#pragma once
#include "Texture2D.h"
#include "Application.h"
#include "kEffect.h"

struct SubMesh {

	GLuint VA, VB;
	int vCount, tCount;
	Texture2D* color;
	Texture2D* normal;
	Texture2D* shadow;
	int vi, ii;

	std::vector<float> verts;
	std::vector<GLuint> indices;


};


class Mesh2D
{
public:

	std::vector<SubMesh*> Sub;
	float dz = 0.01f;
	float zi = 0.001f;


	Mesh2D() {

		Sub.resize(0);

	}

	SubMesh* FindSub(Texture2D* col, Texture2D* norm) {

		for (int i = 0; i < Sub.size(); i++) {

			auto s = Sub[i];
			if (s->color == col && s->normal == norm)
			{
				return s;
			}


		}

		auto newsub = new SubMesh();
		newsub->color = col;
		newsub->normal = norm;
		newsub->verts.resize(0);
		newsub->indices.resize(0);
		newsub->vCount = 0;
		newsub->tCount = 0;
		newsub->vi = 0;
		newsub->ii = 0;
		Sub.push_back(newsub);

		return newsub;

	}
	void AddQuadLM(float x, float y, float w, float h,float u1,float v1,float u2,float v2 ,Texture2D* color, Texture2D* normal, float r, float g, float b, float a)
	{
		auto sub = FindSub(color, normal);


		int vI = sub->ii;
		sub->verts.push_back(x);
		sub->verts.push_back(y);
		sub->verts.push_back(dz);
		sub->verts.push_back(0);
		sub->verts.push_back(0);
		sub->verts.push_back(u1);
		sub->verts.push_back(v1);
		sub->verts.push_back(r);
		sub->verts.push_back(g);
		sub->verts.push_back(b);
		sub->verts.push_back(a);
		sub->verts.push_back(x + w);
		sub->verts.push_back(y);
		sub->verts.push_back(dz);
		sub->verts.push_back(1);
		sub->verts.push_back(0);
		sub->verts.push_back(u2);
		sub->verts.push_back(v1);
		sub->verts.push_back(r);
		sub->verts.push_back(g);
		sub->verts.push_back(b);
		sub->verts.push_back(a);
		sub->verts.push_back(x + w);
		sub->verts.push_back(y + h);
		sub->verts.push_back(dz);
		sub->verts.push_back(1);
		sub->verts.push_back(1);
		sub->verts.push_back(u2);
		sub->verts.push_back(v2);
		sub->verts.push_back(r);
		sub->verts.push_back(g);
		sub->verts.push_back(b);
		sub->verts.push_back(a);
		sub->verts.push_back(x);
		sub->verts.push_back(y + h);
		sub->verts.push_back(dz);
		sub->verts.push_back(0);
		sub->verts.push_back(1);
		sub->verts.push_back(u1);
		sub->verts.push_back(v2);
		sub->verts.push_back(r);
		sub->verts.push_back(g);
		sub->verts.push_back(b);
		sub->verts.push_back(a);
		sub->indices.push_back((GLuint)vI);
		sub->indices.push_back((GLuint)vI + 1);
		sub->indices.push_back((GLuint)vI + 2);
		sub->indices.push_back((GLuint)vI + 3);
		sub->vi += 44;
		sub->ii += 4;

		dz += zi;

	}
	void AddQuad(float x, float y, float w, float h, Texture2D* color, Texture2D* normal,float r,float g,float b,float a)
	{

		auto sub = FindSub(color, normal);


		int vI = sub->ii;
		sub->verts.push_back(x);
		sub->verts.push_back(y);
		sub->verts.push_back(dz);
		sub->verts.push_back(0);
		sub->verts.push_back(0);
		sub->verts.push_back(r);
		sub->verts.push_back(g);
		sub->verts.push_back(b);
		sub->verts.push_back(a);
		sub->verts.push_back(x + w);
		sub->verts.push_back(y);
		sub->verts.push_back(dz);
		sub->verts.push_back(1);
		sub->verts.push_back(0);
		sub->verts.push_back(r);
		sub->verts.push_back(g);
		sub->verts.push_back(b);
		sub->verts.push_back(a);
		sub->verts.push_back(x + w);
		sub->verts.push_back(y + h);
		sub->verts.push_back(dz);
		sub->verts.push_back(1);
		sub->verts.push_back(1);
		sub->verts.push_back(r);
		sub->verts.push_back(g);
		sub->verts.push_back(b);
		sub->verts.push_back(a);
		sub->verts.push_back(x);
		sub->verts.push_back(y + h);
		sub->verts.push_back(dz);
		sub->verts.push_back(0);
		sub->verts.push_back(1);
		sub->verts.push_back(r);
		sub->verts.push_back(g);
		sub->verts.push_back(b);
		sub->verts.push_back(a);
		sub->indices.push_back((GLuint)vI);
		sub->indices.push_back((GLuint)vI + 1);
		sub->indices.push_back((GLuint)vI + 2);
		sub->indices.push_back((GLuint)vI + 3);
		sub->vi += 36;
		sub->ii += 4;
	
		dz += zi;
	}

	void RenderLM() {

		for (int i = 0; i < Sub.size(); i++) {

			auto sub = Sub[i];

			glBindVertexArray(sub->VA);

			glBindBuffer(GL_ARRAY_BUFFER, sub->VB);

			sub->color->Bind(0);
			if (sub->normal != NULL) {
				//		sub->normal->Bind(1);
			}


			GLsizeiptr siz = ((GLsizeiptr)(sub->vi) * 4);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, 11 * 4, 0);





			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, false, 11 * 4, (void*)(3 * 4));



			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, false, 11 * 4, (void*)(7 * 4));

			glDrawElements(GL_QUADS, sub->ii, GL_UNSIGNED_INT, sub->indices.data());


			if (sub->normal != NULL) {
				//sub->normal->Release(1);
			}
			sub->color->Release(0);

		}

	}
	
	void RenderLM(kEffect* fx, bool alpha) {

		fx->bind();

		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		if (alpha) {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else {
			glBlendFunc(GL_ONE, GL_ONE);
		}
		glViewport(0, 0, Application::RenW, Application::RenH);
		glClearDepth(1.0f);
		glDepthFunc(GL_LESS);




		for (int i = 0; i < Sub.size(); i++) {

			auto sub = Sub[i];

			glBindVertexArray(sub->VA);

			glBindBuffer(GL_ARRAY_BUFFER, sub->VB);

			sub->color->Bind(0);
			if (sub->normal != NULL) {
		//		sub->normal->Bind(1);
			}


			GLsizeiptr siz = ((GLsizeiptr)(sub->vi) * 4);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, 11 * 4, 0);





			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, false, 11 * 4, (void*)(3 * 4));



			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, false, 11 * 4, (void*)(7 * 4));

			glDrawElements(GL_QUADS, sub->ii, GL_UNSIGNED_INT, sub->indices.data());


			if (sub->normal != NULL) {
				sub->normal->Release(1);
			}
			sub->color->Release(0);

		}

		fx->unbind();

	}
	void Render() {

		for (int i = 0; i < Sub.size(); i++) {

			auto sub = Sub[i];

			glBindVertexArray(sub->VA);

			glBindBuffer(GL_ARRAY_BUFFER, sub->VB);

			sub->color->Bind(0);
			if (sub->normal != NULL) {
		//		sub->normal->Bind(1);
			}


			GLsizeiptr siz = ((GLsizeiptr)(sub->vi) * 4);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * 4, 0);





			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, false, 9 * 4, (void*)(3 * 4));



			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, false, 9 * 4, (void*)(5 * 4));

			glDrawElements(GL_QUADS, sub->ii, GL_UNSIGNED_INT, sub->indices.data());


			if (sub->normal != NULL) {
			//	sub->normal->Release(1);
			}
			sub->color->Release(0);

		}

	}
	void Render(kEffect* fx,bool alpha) {

		fx->bind();

		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		if (alpha) {
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else {
			glBlendFunc(GL_ONE, GL_ONE);
		}
		glViewport(0, 0, Application::RenW, Application::RenH);
		glClearDepth(1.0f);
		glDepthFunc(GL_LESS);


		

		for (int i = 0; i < Sub.size(); i++) {

			auto sub = Sub[i];

			glBindVertexArray(sub->VA);

			glBindBuffer(GL_ARRAY_BUFFER, sub->VB);

			sub->color->Bind(0);
			if (sub->normal != NULL) {
				sub->normal->Bind(1);
			}


			GLsizeiptr siz = ((GLsizeiptr)(sub->vi) * 4);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * 4, 0);





			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, false, 9 * 4, (void*)(3 * 4));



			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, false, 9 * 4, (void*)(5 * 4));

			glDrawElements(GL_QUADS, sub->ii, GL_UNSIGNED_INT, sub->indices.data());


			if (sub->normal != NULL) {
				sub->normal->Release(1);
			}
			sub->color->Release(0);

		}

		fx->unbind();

	}

	void CompileLM() {

		for (int i = 0; i < Sub.size(); i++) {

			auto sub = Sub[i];

			GLuint va, vb;
			glGenVertexArrays(1, &va);


			glGenBuffers(1, &vb);

			sub->VA = va;
			sub->VB = vb;

			glBindVertexArray(va);

			glBindBuffer(GL_ARRAY_BUFFER, vb);



			GLsizeiptr siz = ((GLsizeiptr)(sub->vi) * 4);

			glBufferData(GL_ARRAY_BUFFER, siz, (const void*)sub->verts.data(), GL_DYNAMIC_DRAW);
			printf("Size:%d\n", (int)siz);


			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, 11 * 4, 0);


			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, false, 11 * 4, (void*)(3 * 4));



			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, false, 11 * 4, (void*)(7 * 4));





			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		}

		//while(true){}
	}



	void Compile() {

		for (int i = 0; i < Sub.size(); i++) {

			auto sub = Sub[i];

			GLuint va, vb;
			glGenVertexArrays(1, &va);


			glGenBuffers(1, &vb);
			
			sub->VA = va;
			sub->VB = vb;

			glBindVertexArray(va);

			glBindBuffer(GL_ARRAY_BUFFER, vb);



			GLsizeiptr siz = ((GLsizeiptr)(sub->vi) * 4);

			glBufferData(GL_ARRAY_BUFFER, siz, (const void*)sub->verts.data() , GL_DYNAMIC_DRAW);
			printf("Size:%d\n", (int)siz);


			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * 4, 0);





			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, false, 9 * 4, (void*)(3 * 4));



			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, false, 9 * 4, (void*)(5 * 4));





			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, 0);


		}

		//while(true){}
	}

};

