class SubstepStarter final {
public:
    bool start() {
        return stepId++ == runId;
    }

    void end() {}

    bool next_run() {
        if (stepCount == -1) {
            stepCount = stepId;
        }
        ++runId;
        stepId = 0;
        return runId < stepCount;
    }

private:
    int runId = 0, stepId = 0, stepCount = -1;
};

#include <iostream>

void run_substep(SubstepStarter &s) {
    if (s.start()) {
        std::cout << '1';
    }
    s.end();

    if (s.start()) {
        std::cout << '2';
    }
    s.end();

    if (s.start()) {
        std::cout << '3';
    }
    s.end();
    std::cout << '#';
}

void run_step(SubstepStarter &s) {
    do {
        run_substep(s);
    } while (s.next_run());
}

int main() {
    SubstepStarter s;
    run_step(s);
    return 0;
}
