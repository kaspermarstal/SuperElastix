..\SuperElastix.exe --conf ..\Configuration\itkv4_SVF_MSD.json --graphout 2B_graph_itkv4_MSD.dot --in FixedImage=..\Data\coneA2d64.mhd MovingImage=..\Data\coneB2d64.mhd --out ResultImage=2B_image_itkv4_MSD.mhd ResultDisplacementField=2B_deformation_itkv4_MSD.mhd

CALL graphviz_to_png 2B_graph_itkv4_MSD.dot