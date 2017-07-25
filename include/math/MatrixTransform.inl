// =============================================================================
// INLINE
// General inlined definitions for MatrixTransform.
// Author: Constantin Masson
// =============================================================================


FORCE_INLINE MatrixF4 MatrixTransform::creaTranslate(VectF3 const& v) {
    return MatrixTransform::creaTranslate(v.x, v.y, v.z);
}

FORCE_INLINE MatrixF4 MatrixTransform::creaTranslate(const float tx, const float ty, const float tz) {
    MatrixF4 momo = MatrixF4::IDENTITY; // Yeah, momo is a cool name
    momo._m[3][0] = tx;
    momo._m[3][1] = ty;
    momo._m[3][2] = tz;
    return momo; // In case of: [3][3] already set to 1 thanks to IDENTITY
}

FORCE_INLINE MatrixF4 MatrixTransform::creaScale(VectF3 const& v) {
    return MatrixTransform::creaScale(v.x, v.y, v.z);
}

FORCE_INLINE MatrixF4 MatrixTransform::creaScale(const float sx, const float sy, const float sz) {
    MatrixF4 soso = MatrixF4::ZERO;
    soso._m[0][0] = sx;
    soso._m[1][1] = sy;
    soso._m[2][2] = sz;
    soso._m[3][3] = 1;
    return soso;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateX(const float angle) {
    MatrixF4 roo = MatrixF4::IDENTITY; // Pronounce "Roooohhh!!!" like if someone does something stupid! :P
    const float c = COSINE(angle);
    const float s = SINE(angle);
    roo._m[1][1] = c;
    roo._m[1][2] = -s;
    roo._m[2][2] = c;
    roo._m[2][1] = s;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateY(const float angle) {
    MatrixF4 roo = MatrixF4::IDENTITY;
    const float c = COSINE(angle);
    const float s = SINE(angle);
    roo._m[0][0] = c;
    roo._m[0][2] = s;
    roo._m[2][0] = -s;
    roo._m[2][2] = c;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateZ(const float angle) {
    MatrixF4 roo = MatrixF4::IDENTITY;
    const float c = COSINE(angle);
    const float s = SINE(angle);
    roo._m[0][0] = c;
    roo._m[0][1] = -s;
    roo._m[1][0] = s;
    roo._m[1][1] = c;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateXYZ(const float rx, const float ry, const float rz){
    MatrixF4 m = MatrixF4::IDENTITY;
    m *= MatrixTransform::creaRotateX(rx);
    m *= MatrixTransform::creaRotateY(ry);
    m *= MatrixTransform::creaRotateZ(rz);
    return m;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaLookAtLH(VectF3 const& cPos, VectF3 const& cTarget, VectF3 const& cUp){
    // Create the 3 Camera vectors.
    VectF3 cx, cy, cz;
    cz = cTarget - cPos;
    cx = VectF3::crossProduct(cUp, cz);
    cy = VectF3::crossProduct(cz, cx);
    cz.normalizeFast();
    cx.normalizeFast();
    cy.normalizeFast();

    // Create the lookAt matrix from camera vectors.
    MatrixF3 m3(cx, cy, cz);
    MatrixF4 m(m3);
    m._m[0][3] = -(VectF3::dotProduct(cx, cPos));
    m._m[1][3] = -(VectF3::dotProduct(cy, cPos));
    m._m[2][3] = -(VectF3::dotProduct(cz, cPos));
    return m;
}


