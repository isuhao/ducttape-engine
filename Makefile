default: bake

clean:
	[[ -d build ]] && rm -r build
	[[ -d docs/doxygen ]] && rm -r docs/doxygen

init:
	mkdir -p build

bake: init
	cd build; cmake ..; make -j3

install:
	echo "Installation not implemented yet."

# Editor

run_editor_client:
	cd bin; ./editor_client

run_editor_server:
	cd bin; ./editor_server	

doc:
	doxygen