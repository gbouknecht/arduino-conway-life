/*
 * During linking of the object files you may get the message:
 *
 *     undefined reference to `__cxa_pure_virtual'
 *
 * Quoted from the internet: "The __cxa_pure_virtual function is an error
 * handler that is invoked when a pure virtual function is called." It was
 * suggested to supply an empty implementation of this function to circumvent
 * this problem. So here it is.
 */

extern "C" void __cxa_pure_virtual(void) {}
