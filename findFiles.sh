echo "SOURCES=\\" > files.mk
find src -name *.cpp -printf '%p\\\n' > files.mk.tmp
cat files.mk.tmp >> files.mk
find src -name *.cxx -printf '%p\\\n' > files.mk.tmp
cat files.mk.tmp >> files.mk
rm files.mk.tmp
