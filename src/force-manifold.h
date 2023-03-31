#pragma once
#include <openvdb/Exceptions.h>
#include <openvdb/openvdb.h>
#include <openvdb/tools/MeshToVolume.h>
#include <openvdb/tools/VolumeToMesh.h>
#include <openvdb/util/Util.h>
#include <vector>
#include <string>

namespace force_mani{ 

	struct MeshData{ 

		std::vector<int> triangles;
		std::vector<float> points;

	};

	MeshData SDFManifold(MeshData &input, float scale=10.0f, float isovalue = 0.55f);


}

