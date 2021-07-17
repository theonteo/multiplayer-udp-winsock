Built on x86

Current engine has multiple areas encapsulated in their own cpp files.

All features implemented.

Vertex Normals computed in Model.cpp using mean weighted method
in ComputeNormals() function. 
line 290~

Cube model loaded at the start.

Other models are loaded when clicking the "Load Model" Button.

Model vertex transform calculated in Model.cpp - ReshapeModel()
line 240~

Model drawing/binding is done on Mesh.cpp - RenderMesh() / RenderNormal()

Model setup/clearing is done in Mesh.cpp

Model transform UI is done in Interface.cpp

Model is lit by vertex lighting using vertex normals. 

Rendering/matrix calculation is handled in Render.cpp

