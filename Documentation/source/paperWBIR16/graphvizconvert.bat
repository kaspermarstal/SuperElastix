REM "c:\Program Files (x86)"\Graphviz2.38\bin\dot C:\wp\SuperElastix\bld2\SuperElastix-build\Testing\Unit\itkv4_SVF_ANTSCC.dot -Tpng -o ScriptedImages\itkv4_SVF_ANTSCC.png
REM "c:\Program Files (x86)"\Graphviz2.38\bin\dot C:\wp\SuperElastix\bld2\SuperElastix-build\Testing\Unit\itkv4_SVF_MSD.dot -Tpng -o ScriptedImages\itkv4_SVF_MSD.png
REM "c:\Program Files (x86)"\Graphviz2.38\bin\dot C:\wp\SuperElastix\bld2\SuperElastix-build\Testing\Unit\elastix_BS_NCC.dot -Tpng -o ScriptedImages\elastix_BS_NCC.png
REM "c:\Program Files (x86)"\Graphviz2.38\bin\dot C:\wp\SuperElastix\bld2\SuperElastix-build\Testing\Unit\elastix_BS_MSD.dot -Tpng -o ScriptedImages\elastix_BS_MSD.png

"c:\Program Files (x86)"\Graphviz2.38\bin\dot itkv4graph.dot -Tpdf -o ScriptedImages\itkv4graph.pdf
"c:\Program Files (x86)"\Graphviz2.38\bin\dot itkv4graph.dot -Tsvg -o ScriptedImages\itkv4graph.svg
"c:\Program Files (x86)"\Graphviz2.38\bin\dot elastixgraph.dot -Tpdf -o ScriptedImages\elastixgraph.pdf
"c:\Program Files (x86)"\Graphviz2.38\bin\dot elastixgraph.dot -Tsvg -o ScriptedImages\elastixgraph.svg