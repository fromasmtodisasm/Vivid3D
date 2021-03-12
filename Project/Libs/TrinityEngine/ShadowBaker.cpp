#include "pch.h"
#include "ShadowBaker.h"
#include "CLImageProcessor.h"

ShadowBaker::ShadowBaker() {

}

void ShadowBaker::SetSize(int w, int h) {

	texW = w;
	texH = h;
	buffer = (unsigned char*)malloc(w * h * 3);

}

void ShadowBaker::SetMap(Map* m) {

	map = m;

}




void ShadowBaker::Bake() {

	int mapW = map->GetW();
	int mapH = map->GetH();

	float xR = (float)(mapW) / (float)(texW);
	float yR = (float)(mapH) / (float)(texH);


	int yr = 0;
	printf("Baking shadow.\n");
	for (int y = 0; y < texH; y++) {
		yr++;
		if (yr > 255) yr = 255;
		for (int x = 0; x < texW; x++) {

			int rx, ry;

			rx = x * xR;
			ry = y * yR;

			if (y > 400) {

				int a = 54;

			}

			PixelInfo pix = map->GetPixelInfo(rx, ry);
			pix.colR = pix.colR;
				pix.colG = pix.colG;
			pix.colB = pix.colB;

			int loc = (y * texW * 3) + x * 3;
			if (pix.shadowCaster) {
				buffer[loc] = (unsigned char)0;// char)pix.colR;
				buffer[loc + 1] = (unsigned char)0;// (char)pix.colG;
				buffer[loc + 2] = (unsigned char)0;// (char)pix.colB;
			}
			else {
				buffer[loc] = (unsigned char)255;
				buffer[loc + 1] = (unsigned char)255;
				buffer[loc + 2] = (unsigned char)255;
			}

		}

	}
	printf("Baking complete.\n");


	if (useGpu) {

		CLImageProcessor* ip1 = new CLImageProcessor();
		ip1->SetSize(texW, texH, false);
		ip1->SetSource("CL/shadowMapper.cl");
		ip1->SetImageBuffer(buffer);
		ip1->SetKernal("shadowMap");
		

		auto lights = map->GetLights();

		float lxR = (float)(texW) / (float)(mapW);
		float lyR = (float)(texH) / (float)(mapH);


		for (int i = 0; i < lights.size(); i++) {

			auto light = lights[i];

			unsigned char* buf = (unsigned char*)malloc(texW * texH * 3);
		

			ip1->SetOutputBuffer(buf);

			float px, py;
			px = light->GetPos().X;
			py = light->GetPos().Y;

			px = px * lxR;
			py = py * lyR;


			ip1->AddIntPar(4, (int)px);
			ip1->AddIntPar(5, (int)py);
		

			ip1->RunKernel(1, 1);

			//printf("Buf0:%d Buf1:%d buf2:%d", (int)buf[0],(int)buf[1],(int)buf[30]);
		
			CLImageProcessor* ip2 = new CLImageProcessor();
			ip2->SetSize(texW, texH, false);
			ip2->SetSource("CL/blurImage.cl");
			ip2->SetImageBuffer(buf);
			ip2->SetKernal("blurImage");

			ip2->AddFloatPar(4,Blur);

			unsigned char* buf2 = (unsigned char*)malloc(texW * texH * 3);
			ip2->SetOutputBuffer(buf2);

			ip2->RunKernel(1, 1);

			free(buf);

			Texture2D* ntex = new Texture2D(buf2, texW, texH, false);

			ntex->SetLoaded(true);
			light->SetBakedShadows(ntex);
			delete ip2;


		}
		delete ip1;
		free(buffer);
		return;
	}

	auto lights = map->GetLights();

	float lxR = (float)(texW) / (float)(mapW);
	float lyR = (float)(texH) / (float)(mapH);


	for (int i = 0; i < lights.size(); i++)
	{

		auto light = lights[i];

		float px, py;
		px = light->GetPos().X;
		py = light->GetPos().Y;

		px = px * lxR;
		py = py * lyR;

		unsigned char* lbuf = (unsigned char*)malloc(texW * texH * 3);

		for (int ly = 0; ly < texH; ly++) {

			for (int lx = 0; lx < texW; lx++) {


				float cx, cy;
				cx = lx;
				cy = ly;
				float xd = px - lx;
				float yd = py - ly;
				if (ly > 400)
				{
					int n = 0;
				}

				int aloc = (cy * texH * 3) + cx * 3;
				if (buffer[aloc] == 0) {
					int aloc = (ly * texW * 3) + lx * 3;
					lbuf[aloc++] = (unsigned char)255;
					lbuf[aloc++] = (unsigned char)255;
					lbuf[aloc++] = (unsigned char)255;
					continue;

				}

				int x1 = cx;
				int y1 = cy;
				int x2 = px;
				int y2 = py;
				bool shadowed = false;
				int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
				dx = x2 - x1;
				dy = y2 - y1;
				dx1 = fabs(dx);
				dy1 = fabs(dy);
				px = 2 * dy1 - dx1;
				py = 2 * dx1 - dy1;
				if (dy1 <= dx1)
				{
					if (dx >= 0)
					{
						x = x1;
						y = y1;
						xe = x2;
					}
					else
					{
						x = x2;
						y = y2;
						xe = x1;
					}
					//putpixel(x, y, c);
					int aloc = (y * texH * 3) + x * 3;
					if (buffer[aloc] == 0) {
						shadowed = true;
						
					}

					for (i = 0; x < xe; i++)
					{
						x = x + 1;
						if (px < 0)
						{
							px = px + 2 * dy1;
						}
						else
						{
							if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
							{
								y = y + 1;
							}
							else
							{
								y = y - 1;
							}
							px = px + 2 * (dy1 - dx1);
						}
						int aloc = (y * texH * 3) + x * 3;
						if (buffer[aloc] == 0) {
							shadowed = true;

						}

					}
				}
				else
				{
					if (dy >= 0)
					{
						x = x1;
						y = y1;
						ye = y2;
					}
					else
					{
						x = x2;
						y = y2;
						ye = y1;
					}
					int aloc = (y * texH * 3) + x * 3;
					if (buffer[aloc] == 0) {
						shadowed = true;

					}
					for (i = 0; y < ye; i++)
					{
						y = y + 1;
						if (py <= 0)
						{
							py = py + 2 * dx1;
						}
						else
						{
							if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
							{
								x = x + 1;
							}
							else
							{
								x = x - 1;
							}
							py = py + 2 * (dx1 - dy1);
						}
						int aloc = (y * texH * 3) + x * 3;
						if (buffer[aloc] == 0) {
							shadowed = true;

						}
					}
				}




				if (shadowed) {

					int aloc = (ly * texW * 3) + lx * 3;
					lbuf[aloc++] = (unsigned char)0;
					lbuf[aloc++] = (unsigned char)0;
					lbuf[aloc++] = (unsigned char)0;

				}
				else {
					int aloc = (ly * texW * 3) + lx * 3;
					lbuf[aloc++] = (unsigned char)255;
					lbuf[aloc++] = (unsigned char)255;
					lbuf[aloc++] = (unsigned char)255;

				}

				//	}





			}
		}
		

		Texture2D* ntex = new Texture2D((unsigned char*)lbuf, texW, texH, false);
		ntex->SetLoaded(true);
		light->SetBakedShadows(ntex);


	}


	



}