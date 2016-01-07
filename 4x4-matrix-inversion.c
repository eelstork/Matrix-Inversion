
float invf(int i, int j, const float* m){
    int o = 2+(j-i);
    i += 4+o;
    j += 4-o;
    #define e(a,b) m[ ((j+b)%4)*4 + ((i+a)%4) ]
    float inv =
      + e(+1,-1) * e(+0,+0) * e(-1,+1)
      + e(+1,+1) * e(+0,-1) * e(-1,+0)
      + e(-1,-1) * e(+1,+0) * e(+0,+1)
      - e(-1,-1) * e(+0,+0) * e(+1,+1)
      - e(-1,+1) * e(+0,-1) * e(+1,+0)
      - e(+1,-1) * e(-1,+0) * e(+0,+1);
    return (o%2)?inv : -inv;
    #undef e
}

bool inverseMatrix4x4(const float *m, float *out){
    float inv[16];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) inv[j*4+i] = invf(i,j,m);
    double D = 0;
    for(int k=0;k<4;k++) D += m[k] * inv[k*4];
    if (D == 0) return false;
    D = 1.0 / D;
    for (int i = 0; i < 16; i++)
        out[i] = inv[i] * D;
    return true;
}
