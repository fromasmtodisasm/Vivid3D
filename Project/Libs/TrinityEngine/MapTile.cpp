#include "pch.h"
#include "MapTile.h"
#include "Texture2D.h"
#include "VFile.h"

MapTile::MapTile() {

	Image = NULL;
	Normal = NULL;
	Shadow = NULL;
	CastShadows = false;
	RecvShadows = false;
	Collider = false;
	meta.resize(0);

}

MapTile::MapTile(Texture2D* img) {

	Image = img;
	Normal = NULL;
	Shadow = new Texture2D("Edit/shadowDefault.png", false);

	CastShadows = false;
	RecvShadows = false;
	meta.resize(0);
	Collider = false;

};

void MapTile::Save() {

	printf("Saving tile.\n");

	VFile* fil = new VFile((const char*)DataPath, FileMode::Write);

	if (Image != NULL) {

		fil->WriteBool(true);
		Image->Write(fil);
	}
	else {
		fil->WriteBool(false);
	}

	if (Normal != NULL) {

		fil->WriteBool(true);
		Normal->Write(fil);

	}
	else {
		fil->WriteBool(false);
	}

	if (Shadow != NULL) {

		fil->WriteBool(true);
		Shadow->Write(fil);
	}
	else {
		fil->WriteBool(false);
	}

	fil->WriteBool(Collider);
	fil->WriteBool(CastShadows);
	fil->WriteBool(RecvShadows);

	fil->WriteInt(0);
	
	fil->Close();

	printf("Saved.\n");

}

MapTile::MapTile(const char* path) {

	char* result = (char*)malloc(500);

	strcpy(result, path);
	strcat(result, ".td");

	printf("Checking:");
	printf(result);
	printf("\n");
	
	DataPath = result;

	if (VFile::Exists((const char*)&result[0])) {

		printf("File exists. Reading.\n");

		VFile* fil = new VFile((const char*)result,FileMode::Read);

		if (fil->ReadBool()) {

			Texture2D* tex = new Texture2D(fil);
			Image = tex;

		}

		if (fil->ReadBool()) {

			Texture2D* ntex = new Texture2D(fil);
			Normal = ntex;

		}

		if (fil->ReadBool()) {

			Texture2D* stex = new Texture2D(fil);
			Shadow = stex;

		}

		Collider = fil->ReadBool();
		CastShadows = fil->ReadBool();
		RecvShadows = fil->ReadBool();

		int mc = fil->ReadInt();
		

		fil->Close();


	}
	else {

		printf("File does not exists. Creating.\n");
		VFile* fil = new VFile((const char*)result,FileMode::Write);

		Texture2D* tex = new Texture2D(path, true,true);

		fil->WriteBool(true);
		tex->Write(fil);
		fil->WriteBool(true);
		Normal = new Texture2D("map/nm1.png", false);
		Normal->UntilLoaded();
		Normal->Write(fil);
		fil->WriteBool(true);
		Shadow = new Texture2D("Edit/shadowDefault.png", false);
		Shadow->UntilLoaded();
		Shadow->Write(fil);
		fil->WriteBool(Collider);
		fil->WriteBool(CastShadows);
		fil->WriteBool(RecvShadows);

		fil->WriteInt(0);

		Image = tex;
		

		//fil->WriteInt(24);



		fil->Close();

	}




};

MapTile::MapTile(MapTile* tile) {
	 
	Image = tile->GetImage();

};

Texture2D* MapTile::GetImage() {
	
	return Image;

};