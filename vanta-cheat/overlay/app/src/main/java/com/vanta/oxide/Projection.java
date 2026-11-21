package com.vanta.oxide;

/** Простейшая World→Screen без матрицы: через fov+forward. Работает когда view_proj не передан. */
public final class Projection {

    /** Возвращает true если точка перед камерой. out[0]=sx, out[1]=sy. */
    public static boolean worldToScreenSimple(float wx, float wy, float wz,
                                              float cx, float cy, float cz,
                                              float fx, float fy, float fz,
                                              float fovDeg, int sw, int sh,
                                              float[] out) {
        float dx = wx - cx, dy = wy - cy, dz = wz - cz;
        // forward.z
        float fwdLen = (float)Math.sqrt(fx*fx + fy*fy + fz*fz);
        if (fwdLen < 1e-5f) return false;
        fx /= fwdLen; fy /= fwdLen; fz /= fwdLen;

        // right = normalize(cross(forward, up(0,1,0)))
        float rx = fz, ry = 0, rz = -fx;
        float rLen = (float)Math.sqrt(rx*rx + rz*rz);
        if (rLen < 1e-5f) return false;
        rx /= rLen; rz /= rLen;
        // up = cross(right, forward)
        float ux = ry*fz - rz*fy;
        float uy = rz*fx - rx*fz;
        float uz = rx*fy - ry*fx;

        // проекции
        float dFwd = dx*fx + dy*fy + dz*fz;
        if (dFwd < 0.1f) return false;
        float dRight = dx*rx + dy*ry + dz*rz;
        float dUp    = dx*ux + dy*uy + dz*uz;

        float fovRad = (float)Math.toRadians(fovDeg);
        float tanHalf = (float)Math.tan(fovRad * 0.5f);
        float aspect = (float)sw / Math.max(1, sh);
        float ndcX = dRight / (dFwd * tanHalf * aspect);
        float ndcY = dUp    / (dFwd * tanHalf);

        out[0] = (ndcX * 0.5f + 0.5f) * sw;
        out[1] = (1f - (ndcY * 0.5f + 0.5f)) * sh;
        return true;
    }
}
