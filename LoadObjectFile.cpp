#include <string>
#include <math.h>
//#include <iostream>
#include <fstream>
#include "gl/glut.h"   // - An interface and windows management library

#include "LoadObjectFile.h"

using namespace std;



void LoadObjectFile(char* str, model *md)
{
	string line;

	md->num_vertices = 0;
	md->num_faces = 0;

	ifstream count(str);									// Open the file for reading OBJINFO.TXT
   
	if (count.fail()) 
		exit(1);

	while( !count.eof() )
	{
		getline(count, line);

		if(line.substr(0,2) == "v ")
		{
			md->num_vertices++;
		}
		else if(line.substr(0,2) == "f ")
		{
			md->num_faces++;
		}
		else if(line.substr(0,3) == "vn ")
		{
		}
	}

	count.close();

	cout << "v read: " << md->num_vertices << "\n";
	cout << "f read: " << md->num_faces << "\n";

	// Allocate memory

	md->vertices = (struct point*) malloc(md->num_vertices * sizeof(struct point));
	md->faces = (struct face*) malloc(md->num_faces * sizeof(struct face));

	ifstream obj_file(str);

	if (obj_file.fail()) 
		exit(1);

	int vcell=0;
	int fcell=0;
	while( !obj_file.eof() )
	{
		getline(obj_file, line);

		if(line.substr(0,2) == "v ")
		{
			vinsert(md->vertices[vcell], line);
			vcell++;
		}
		else if(line.substr(0,2) == "f ")
		{
			//finsert(md->faces[fcell], line);
			finsert2(md->faces[fcell], line);
			fcell++;
		}
		else if(line.substr(0,3) == "vn ")
		{
		}
		else {}
	}

	obj_file.close();

	//for(int k=0; k<md->num_vertices; k++)
	//	cout << "v  " << md->vertices[k].x << " " << md->vertices[k].y << " " << md->vertices[k].z << "\n";

	/*
	for(int k=0; k<md->num_faces; k++) {
		if(md->faces[k].vtx[3]==-1)
			cout << "f  " << md->faces[k].vtx[0] << " " << md->faces[k].vtx[1] << " " << md->faces[k].vtx[2] << "\n";
		else
			cout << "f  " << md->faces[k].vtx[0] << " " << md->faces[k].vtx[1] << " " << md->faces[k].vtx[2] << " " << md->faces[k].vtx[3] << "\n";
	}
	*/

}

void DisplayModel(model *md)
{
		
//		glBegin(GL_TRIANGLES);
		glBegin(GL_POLYGON);
		for(int i=0; i<md->num_faces; i++) {
			glVertex3f(md->vertices[md->faces[i].vtx[0]].x, md->vertices[md->faces[i].vtx[0]].y, md->vertices[md->faces[i].vtx[0]].z);
			glVertex3f(md->vertices[md->faces[i].vtx[1]].x, md->vertices[md->faces[i].vtx[1]].y, md->vertices[md->faces[i].vtx[1]].z);
			glVertex3f(md->vertices[md->faces[i].vtx[2]].x, md->vertices[md->faces[i].vtx[2]].y, md->vertices[md->faces[i].vtx[2]].z);
			if(md->faces[i].vtx[3]!=-1)
				glVertex3f(md->vertices[md->faces[i].vtx[3]].x, md->vertices[md->faces[i].vtx[3]].y, md->vertices[md->faces[i].vtx[3]].z);
		}
		glEnd();

}

/////////////////////////////////////////////////////


void vinsert(struct point& p, string& str)
{
	int pos=0;
	int cell=0;
	string tmp;

	while(pos < str.length())
	{
		while(pos < str.length())
		{
			if( !( ( str[pos]>='0' && str[pos]<='9' ) || str[pos] == '.' || str[pos]=='-' ) )
			{
				pos++;
			}
			else break;
		}

		while(pos < str.length())
		{
			if( ( str[pos]>='0' && str[pos]<='9' ) || str[pos] == '.' || str[pos]=='-' )
			{
				tmp.append(1, str[pos]);
				pos++;
				if(pos!=str.length())
					continue;
			}

			if(cell==0) {
				p.x = atof(tmp.c_str());
				cell++; 
				tmp.erase();
			}
			else if(cell==1) {
				p.y = atof(tmp.c_str());
				cell++; 
				tmp.erase();
			}
			else if(cell==2) {
				p.z = atof(tmp.c_str());
				cell++; 
				tmp.erase();
			}

			break;
			
		}
	}
}

void finsert(struct face& f, std::string& str)
{
	int pos=0;
	int slash=0;
	string tmp;

	while(pos < str.length())
	{
		while(pos < str.length())
		{
			if( !( str[pos]>='0' && str[pos]<='9' ) )
			{
				if(str[pos]=='/') slash++;
				pos++;
			}
			else break;
		}

		while(pos < str.length())
		{
			if( str[pos]>='0' && str[pos]<='9' )
			{
				tmp.append(1, str[pos]);
				pos++;
				if(pos!=str.length())
					continue;
			}

			if(slash==0) {
				f.vtx[0] = atoi(tmp.c_str());
				f.vtx[0]--;
				tmp.erase();
			}
			else if(slash==2) {
				f.vtx[1] = atoi(tmp.c_str());
				f.vtx[1]--;
				tmp.erase();
			}
			else if(slash==4) {
				f.vtx[2] = atoi(tmp.c_str());
				f.vtx[2]--;
				tmp.erase();
			}

			break;
			
		}
	}
}

void finsert2(struct face& f, std::string& str)
{
	int pos=0;
	int cell=0;
	string tmp;

	f.vtx[3]=-1;

	while(pos < str.length())
	{
		while(pos < str.length())
		{
			if( !( ( str[pos]>='0' && str[pos]<='9' ) || str[pos] == '.' || str[pos]=='-' ) )
			{
				pos++;
			}
			else break;
		}

		while(pos < str.length())
		{
			if( ( str[pos]>='0' && str[pos]<='9' ) || str[pos] == '.' || str[pos]=='-' )
			{
				tmp.append(1, str[pos]);
				pos++;
				if(pos!=str.length())
					continue;
			}

			if(cell==0) {
				f.vtx[0] = atoi(tmp.c_str());
				f.vtx[0]--;
				cell++; 
				tmp.erase();
			}
			else if(cell==1) {
				f.vtx[1] = atoi(tmp.c_str());
				f.vtx[1]--;
				cell++; 
				tmp.erase();
			}
			else if(cell==2) {
				f.vtx[2] = atoi(tmp.c_str());
				f.vtx[2]--;
				cell++; 
				tmp.erase();
			}
			else if(cell==3) {
				f.vtx[3] = atoi(tmp.c_str());
				f.vtx[3]--;
				cell++;
				tmp.erase();			
			}

			break;
			
		}
	}
}










///////////////////////////////////////

// generate a random number in the range from [M,N):
double randfloat(double M, double N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;  
}
