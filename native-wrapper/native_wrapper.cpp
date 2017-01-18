#include "ensitlm.h"
#include "native_wrapper.h"

/*
 * The C compiler does a bit of magic on the main() function. Trick it
 * by changing the name to something else.
 */
#define main __start
/* Time between two step()s */
static const sc_core::sc_time PERIOD(1, sc_core::SC_MS);
/* extern "C" is needed since the software is compiled in C and
 * is linked against native_wrapper.cpp, which is compiled in C++.
 */
extern "C" int main();
extern "C" void interrupt_handler();

extern "C" void write_mem(uint32_t addr, uint32_t data) {
	NativeWrapper::get_instance()->write_mem(addr, data);
}

extern "C" unsigned int read_mem(uint32_t addr) {
	unsigned int data = NativeWrapper::get_instance()->read_mem(addr);
	return data;
}

extern "C" void cpu_relax() {
	NativeWrapper::get_instance()->cpu_relax();
}

extern "C" void wait_for_irq() {
	NativeWrapper::get_instance()->wait_for_irq();
}

/* To keep it simple, the soft wrapper is a singleton, we can
 * call its methods in a simple manner, using
 * NativeWrapper::get_instance()->method_name()
 */
NativeWrapper * NativeWrapper::get_instance() {
	static NativeWrapper * instance = NULL;
	if (!instance)
		instance = new NativeWrapper("native_wrapper");
	return instance;
}

NativeWrapper::NativeWrapper(sc_core::sc_module_name name) : sc_module(name),
							     irq("irq")
{
	SC_THREAD(compute);
	SC_METHOD(interrupt_handler_internal);
	sensitive << irq.pos();
}

void NativeWrapper::write_mem(unsigned int addr, unsigned int data) {
	if (NativeWrapper::socket.write(addr, data) != tlm::TLM_OK_RESPONSE) {
		std::cerr << "erreur de write mem native" << std::endl;
	}
}

unsigned int NativeWrapper::read_mem(unsigned int addr) {
	unsigned int localbuf = 0;
	if (NativeWrapper::socket.read(addr, localbuf) != tlm::TLM_OK_RESPONSE){
		std::cerr << "erreur de read meme native" << std::endl;
	}
	return localbuf;
}

void NativeWrapper::cpu_relax() {
	wait(PERIOD);
}

void NativeWrapper::wait_for_irq() {
	main();
	if (!interrupt)
		wait(interrupt_event);
	interrupt = false;
}

void NativeWrapper::compute() {
	wait_for_irq();
}

void NativeWrapper::interrupt_handler_internal() {
	if (irq.posedge()) {
		interrupt = true;
		interrupt_event.notify();
		interrupt_handler();
	}
}
