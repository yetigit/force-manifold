
#include "tiny_obj_loader.h"
#include "ObjWriter.hpp"
#include "force-manifold.h"
#include <string>
#include <vector>
#include <iostream>


void ReadOBJ(const std::string &obj_file,
             std::vector<float> &vert_pos,
             std::vector<int> &tri_ind){
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;

  tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, obj_file.c_str());

  for (double vertice : attrib.vertices){
    vert_pos.push_back(vertice);

  }

  for (auto &shape : shapes){
    for (auto &indice : shape.mesh.indices){
      tri_ind.push_back(indice.vertex_index);
    }
  }
}


int write_obj(std::string path, const force_mani::MeshData<>  &  mdata)
{
    std::fstream file;
	file.open(path, std::ios::out);
	objwriter::ObjWriter w(file);

	for (size_t i = 0; i < mdata.points.size(); i+= 3)
	{
		w.vertex(
			mdata.points[i + 0],
			mdata.points[i + 1],
			mdata.points[i + 2]);
	}

	for (size_t i = 0; i < mdata.triangles.size(); i+= 3)
	{
		w.face(
			mdata.triangles[i + 0] + 1,
			mdata.triangles[i + 1] + 1,
			mdata.triangles[i + 2] + 1);
	}

	// make a cube

	
	file.close();
	return 1;
}

int main(int argc, char *argv[]){

    std::vector<float> vert_pos;
    std::vector<int> tri_ind; 

#if 1
	if (argc < 3)
	{
		std::cerr << "provide [input path] [output path]\n";
		return -1;
	}

    char * inpath = argv[1];
    char * outpath =argv[2];
	float scalo = 10.f; 

	if (argc > 3)
	{
      scalo = std::atof(argv[3]);
	}


#else
	
	char * inpath = "c:/users/baidh/desktop/chairy.obj";
	char * outpath = "c:/users/baidh/desktop/chairo.obj";
	float scalo = 10.f; 

#endif 
	if (scalo <= 0.f)
	{
		std::exit(-1);
	}

    ReadOBJ(inpath, vert_pos, tri_ind); 

	force_mani::MeshData<> input;
	input.triangles = std::move(tri_ind);
	input.points = std::move(vert_pos);

	force_mani::MeshData<> output = force_mani::SDFManifold(input, scalo);

	for (float&  px : output.points)
	{
		px /= scalo;
	}

	if (!write_obj(outpath, output))
	{
		return -1;
	}


 	return 0;
}