xsdcxx cxx-tree  --cxx-suffix .cpp --hxx-suffix .h --output-dir src/  config.xsd
xsdcxx cxx-tree  --cxx-suffix .cpp --hxx-suffix .h --output-dir src/ --generate-serialization simulation.xsd
xsdcxx cxx-tree  --cxx-suffix .cpp --hxx-suffix .h --output-dir src/outputWriter/ --generate-serialization src/outputWriter/vtk-unstructured.xsd
