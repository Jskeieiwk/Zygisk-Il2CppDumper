// A failed optional HUD hook must not stop player/camera tracking.
export function createHookSet(base, interceptor, log = console.log) {
  const listeners = [], states = {},labels=new Map();
  let active = true;
  return {
    attach(rva, callbacks, label, required = false) {
      if (!active) throw Error('Hook set already detached');
      if(labels.has(label))return true;
      try {
        const listener = interceptor.attach(base.add(rva), callbacks);
        listeners.push(listener);labels.set(label,listener);
        states[label] = true;
        return true;
      } catch (error) {
        states[label] = false;
        log('CLOUD:hook-unavailable ' + label + ' rva=' + rva.toString(16) + ' ' + error);
        if (required) throw error;
        return false;
      }
    },
    states() { return {...states}; },
    remove(label){
      const listener=labels.get(label);if(!labels.has(label))return;
      labels.delete(label);const index=listeners.indexOf(listener);if(index>=0)listeners.splice(index,1);
      if(listener&&listener.detach)listener.detach();if(states[label]===true)delete states[label];
    },
    detach() {
      active = false;labels.clear();
      for (const listener of listeners.splice(0).reverse()) {
        try { if (listener && listener.detach) listener.detach(); }
        catch (error) { log('CLOUD:hook-detach-error ' + error); }
      }
    }
  };
}
