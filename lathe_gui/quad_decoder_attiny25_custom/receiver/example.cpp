#include <avr/io.h>
#include <receiver.h>

int main(int argc, char ** argv)
{
	quad_receiver_t q;
	quad_receive(0, &q);
	quad_receive(1, &q);
}
