
int getLoc(int x,int y,int mW,int mH){

    return (y*mW*3)+x*3;

}

void kernel lightMap(global const uchar* A, global uchar* B,int mW,int mH,float lX,float lY,float lRad,float lr,float lg,float lb ){       
    //C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                 
    //printf("Testing!");
    
    int i = get_global_id(0);

    int x,y;

    y = i / mW;

    x = i - (y*mW);

    int ox,oy;
    ox = x;
    oy = y;

    int r,g,b;
    
    r=0;
    g=0;
    b=0;


    float xd = lX-(float)ox;
    float yd = lY-(float)oy;

    float mag = sqrt(xd*xd+yd*yd);

    mag = mag / lRad;

    if(mag>1.0) mag = 1.0;
    mag = 1.0-mag;

    int bloc = getLoc(ox,oy,mW,mH);

    uchar br,bg,bb;

    br = (uchar)((lr*mag)*255.0);
    bg = (uchar)((lg*mag)*255.0);
    bb = (uchar)((lb*mag)*255.0);


    B[bloc] = br;
    B[bloc+1] = bg;
    B[bloc+2] = bb;



    //printf("Lx:%d Ly:%d lRad:%f R:%f G:%f B:%f\n",(int)lX,(int)lY,lRad,lr,lg,lb);
  
    
  
    

   

            
}


