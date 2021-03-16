
int getLoc(int x,int y,int mW,int mH){

    return (y*mW*3)+x*3;

}

void kernel shadowMap(global const uchar* A, global uchar* B,int mW,int mH,int lX,int lY){       
    //C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                 
    //printf("Testing!");
    
    int i = get_global_id(0);

    int x,y;

    y = i / mW;

    x = i - (y*mW);

    int ox,oy;
    ox = x;
    oy = y;

   // printf("X:%d Y:%d\n",x,y);




    int loc = getLoc(x,y,mW,mH);


    float steps = 128;

    float xd = (float)lX-(float)x;
    float yd = (float)lY-(float)y;

    xd = xd / steps;
    yd = yd / steps;

    uchar pv = 255;

    float px,py;

    px = (float)x;
    py = (float)y;

    if(A[getLoc(x,y,mW,mH)]==0)
    {

          loc = getLoc(ox,oy,mW,mH);

        B[loc] = 255;
        B[loc+1] = 255;
        B[loc+2] = 255;
        return;


    }

    float s1 = 0.0;
    float num = 0.0;

    for(int i=0;i<steps;i++){

        uchar sv = A[getLoc((int)px,(int)py,mW,mH)];

        if(sv==0)
        {

            //pv = 0;
            s1 = s1 + 8.0;
            num=num+1.0;
        }

        px = px + xd;
        py = py + yd;
    }

    if(s1>0){

        pv = 0;

    }else{

        pv = 255;

    }

    loc = getLoc(ox,oy,mW,mH);

    B[loc] = pv;
    B[loc+1] = pv;
    B[loc+2] = pv;

    //B[rloc] = (uchar)r;
   // B[rloc+1] = (uchar)r;
  //  B[rloc+2] = (uchar)r;


//    printf("X:%d Y:%d\n",x,y);

    //printf("mW:%d mH:%d lX:%d lY:%d \n",mW,mH,lX,lY);
            
}


