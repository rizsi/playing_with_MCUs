EMCC_EXPORTED_FUNCTIONS = '["_setup", "_main", "_loop", "_getSegmentValues", "_setInput", "_buttonPressed", "_updateTime", "_loadDataCallback"]'

SRCS = gui_port_emscripten.cpp ../gui/lathe_gui.cpp
INCLUDES = -I../gui

all: gui_port_emscripten.js

gui_port_emscripten.js: ${SRCS}
	emcc ${SRCS} ${INCLUDES} \
	-o gui_port_emscripten.js \
	-s EXPORTED_FUNCTIONS=${EMCC_EXPORTED_FUNCTIONS} -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'

run:
	emrun --no_browser --port 8080 .

clean:
	rm -f gui_port_emscripten.js gui_port_emscripten.wasm

