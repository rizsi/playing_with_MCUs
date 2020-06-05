
# Functions are exported by CPP files using EMSCRIPTEN_KEEPALIVE keyword.
EMCC_EXPORTED_FUNCTIONS = '["_main"]'

SRCS = gui_port_emscripten.cpp ../common/auto_watering.cpp ../../libraries/rizsi_DRAW/src/rizsi_DRAW.cpp
INCLUDES = -I . -I../common -I ../../libraries/rizsi_DRAW/src

all: gui_port_emscripten.js

gui_port_emscripten.js: ${SRCS}
	emcc ${SRCS} ${INCLUDES} \
	-o gui_port_emscripten.js \
	-s EXPORTED_FUNCTIONS=${EMCC_EXPORTED_FUNCTIONS} -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'

run:
	emrun --no_browser --port 8080 .

clean:
	rm -f gui_port_emscripten.js gui_port_emscripten.wasm

