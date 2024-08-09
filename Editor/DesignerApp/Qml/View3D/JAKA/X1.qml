import QtQuick
import QtQuick3D
Node {
    id: x1_obj
    Model {
        id: defaultobject
        source: "meshes/defaultobject.mesh"

        DefaultMaterial {
            id: defaultMaterial_material
            diffuseColor: "#ff999999"
        }
        materials: [
            defaultMaterial_material
        ]
    }
}
