"""Read selected ZIP entries from a public MEGA link without storing game assets.

Extracted entries are checked by zipfile's CRC verification. This does not verify
MEGA's full-file MAC, which requires reading the entire file.
"""
import base64
import io
import json
import sys
import urllib.request
import zipfile
from pathlib import Path
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes


class MegaFile(io.RawIOBase):
    def __init__(self, link):
        handle, key_text = link.split('/file/', 1)[1].split('#', 1)
        raw = base64.urlsafe_b64decode(key_text + '=' * (-len(key_text) % 4))
        if len(raw) != 32:
            raise ValueError('Expected a 256-bit MEGA file key')
        words = [int.from_bytes(raw[i:i+4], 'big') for i in range(0, 32, 4)]
        self.key = b''.join((words[i] ^ words[i+4]).to_bytes(4, 'big') for i in range(4))
        self.iv = int.from_bytes(raw[16:24] + bytes(8), 'big')
        req = urllib.request.Request('https://g.api.mega.co.nz/cs?id=1',
            data=json.dumps([{'a':'g', 'g':1, 'p':handle}]).encode(),
            headers={'Content-Type':'application/json'})
        with urllib.request.urlopen(req, timeout=30) as response:
            info = json.load(response)[0]
        if not isinstance(info, dict) or 'g' not in info:
            raise ValueError('MEGA did not provide a download URL')
        self.url, self.size, self.offset = info['g'], info['s'], 0
        self.cache = {}

    def seekable(self): return True
    def readable(self): return True
    def tell(self): return self.offset
    def seek(self, offset, whence=0):
        target = offset if whence == 0 else self.offset + offset if whence == 1 else self.size + offset
        if target < 0: raise ValueError('Negative seek')
        self.offset = target
        return target

    def block(self, index):
        if index in self.cache: return self.cache[index]
        start = index * 1024 * 1024
        end = min(start + 1024 * 1024, self.size) - 1
        with urllib.request.urlopen(self.url + '/' + str(start) + '-' + str(end), timeout=45) as response:
            data = response.read(end-start+2)
        if len(data) != end-start+1:
            raise IOError('Unexpected range response length')
        decoder = Cipher(algorithms.AES(self.key), modes.CTR((self.iv + start//16).to_bytes(16, 'big'))).decryptor()
        result = decoder.update(data) + decoder.finalize()
        if len(self.cache) >= 8: self.cache.pop(next(iter(self.cache)))
        self.cache[index] = result
        return result

    def read(self, size=-1):
        if size < 0: size = self.size-self.offset
        remaining = min(size, self.size-self.offset)
        output = []
        while remaining > 0:
            index, offset = divmod(self.offset, 1024*1024)
            data = self.block(index)[offset:offset+remaining]
            if not data: raise IOError('Empty range')
            output.append(data)
            self.offset += len(data)
            remaining -= len(data)
        return b''.join(output)


if __name__ == '__main__':
    source = MegaFile(sys.argv[1])
    output = Path(sys.argv[2]); output.mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(source) as archive:
        entries = [{'name':i.filename, 'size':i.file_size, 'compressed':i.compress_size, 'crc32':i.CRC}
                   for i in archive.infolist()]
        (output/'entries.json').write_text(json.dumps(entries, indent=2))
        print('Archive:', source.size, 'bytes,', len(entries), 'entries', flush=True)
        for name in sys.argv[3:]:
            path = output / name
            if path.resolve().is_relative_to(output.resolve()):
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(archive.read(name))
                print('CRC verified:', name, path.stat().st_size, flush=True)
