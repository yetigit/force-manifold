#include "force-manifold.h"

namespace force_mani
{
	force_mani::MeshData<> SDFManifold(MeshData<>& input, float scale, float isovalue)
	{
		using namespace openvdb;

		std::vector<Vec3s> points;
		std::vector<Vec3I> tris;

		//points.resize(input.points.size() / 3);
		//memcpy(points.data(), input.points.data(), sizeof(float) * input.points.size());


        for (int i = 0; i < input.points.size(); i+=3)
        {
            points.push_back({input.points[i+0]*scale, input.points[i+1]*scale, input.points[i+2]*scale});
        }

		tris.resize(input.triangles.size() / 3);
		memcpy(tris.data(), input.triangles.data(), sizeof(int) * input.triangles.size());

		math::Transform::Ptr xform = math::Transform::createLinearTransform();
		tools::QuadAndTriangleDataAdapter<Vec3s, Vec3I> mesh(points, tris);

		DoubleGrid::Ptr sgrid = tools::meshToSignedDistanceField<DoubleGrid>(
			*xform, points, tris, std::vector<Vec4I>(), 3.0f, 3.0f);

		auto& newPoints = points;
		std::vector<Vec3I> newTriangles;
		std::vector<Vec4I> newQuads;
		tools::volumeToMesh(*sgrid, points, newTriangles, newQuads, isovalue);

		force_mani::MeshData<> output;
		output.points.resize(newPoints.size() * 3);
		memcpy(output.points.data(), newPoints.data(), sizeof(float) * 3 * newPoints.size());


		output.triangles.resize((newTriangles.size() * 3) + (newQuads.size() * 6));
		memcpy(output.triangles.data(), newTriangles.data(), sizeof(int) * 3 * newTriangles.size());


		for (int i = 0, start = newTriangles.size( )  * 3 ; i < newQuads.size(); ++i)
        {
			output.triangles[start++] = newQuads[i][0];
			output.triangles[start++] = newQuads[i][1];
			output.triangles[start++] = newQuads[i][2];
			output.triangles[start++] = newQuads[i][2];
			output.triangles[start++] = newQuads[i][3];
			output.triangles[start++] = newQuads[i][0];
        }

		std:reverse(output.triangles.begin(), output.triangles.end());

		return output;
	}

}