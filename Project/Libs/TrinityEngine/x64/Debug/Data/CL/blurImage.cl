
int getLoc(int x,int y,int mW,int mH){

    return (y*mW*3)+x*3;

}

void kernel blurImage(global const uchar* A, global uchar* B,int mW,int mH,float blurA){       
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
    int num =0;

    for(int dy=y-8;dy<y+8;dy++){
    for(int dx=x-8;dx<x+8;dx++){

        float xo  = dx-x;
        float yo = dy-y;

        xo = xo * blurA;
        yo = yo * blurA;

        int ux = x + xo;
        int uy = y + yo;  

        int nloc = getLoc(ux,uy,mW,mH);

        r = r + A[nloc];
        g = g + A[nloc+1];
        b = b + A[nloc+2];

        num = num +1;
    }
    }

    r = r / num;
    g = g / num;
    b = b / num;

    int loc = getLoc(x,y,mW,mH);

    B[loc] = (uchar)r;
    B[loc+1] = (uchar)g;
    B[loc+2] = (uchar)b;



    
  
    

   

            
}


