EMCC_EXPORTED_FUNCTIONS = '["_setup", "_main", "_loop", "_buttonPressed", "_updateTime"]'

SRCS = gui_port_emscripten.cpp fozolap.cpp
INCLUDES = -I./

all: gui_port_emscripten.js

gui_port_emscripten.js: ${SRCS}
	emcc ${SRCS} ${INCLUDES} \
	-o gui_port_emscripten.js \
	-s EXPORTED_FUNCTIONS=${EMCC_EXPORTED_FUNCTIONS} -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'

run: gui_port_emscripten.js
	emrun --no_browser --port 8080 .

clean:
	rm -f gui_port_emscripten.js gui_port_emscripten.wasm

