function fibonacci(n) {
    return n < 1 ? 0
        : n <= 2 ? 1
            : fibonacci(n - 1) + fibonacci(n - 2);
}


function demo() {
    // return "JS result -- evaluated by V8. " + fibonacci(10);
    // print(10);
    return JSON.stringify({"foo": Returns42F(2) },null,2);
}

demo();


