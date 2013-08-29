#pragma once

#include "MeshParser.h"

#include <list>
#include <vector>
#include <string>

#include "EigenTypedef.h"

class OBJParser : public MeshParser {
    // TODO: only triangular mesh is supported
    public:
        typedef MeshParser::AttrNames AttrNames;
        virtual ~OBJParser() {}

        virtual bool parse(const std::string& filename);

        // Only extract surface in obj file.
        virtual size_t vertex_per_voxel() const { return 0; };

        virtual size_t num_vertices() const {return m_vertices.size();}
        virtual size_t num_faces() const {return m_faces.size();}
        virtual size_t num_voxels() const {return m_voxels.size();}
        virtual size_t num_attributes() const;

        virtual AttrNames get_attribute_names() const;
        virtual size_t get_attribute_size(const std::string& name) const;

        virtual void export_vertices(Float* buffer);
        virtual void export_faces(int* buffer);
        virtual void export_voxels(int* buffer);
        virtual void export_attribute(const std::string& name, Float* buffer);

    protected:
        bool has_normals() const;
        bool attribute_exists(const std::string& name) const;
        bool parse_vertex_line(char* line);
        bool parse_face_line(char* line);

        typedef std::list<Vector3F> VertexList;
        typedef std::list<Vector3I> FaceList;
        typedef std::list<VectorI>  VoxelList;
        typedef std::list<Vector3F> NormalList;

        VertexList m_vertices;
        FaceList   m_faces;
        VoxelList  m_voxels;
        NormalList m_vertex_normals;
};