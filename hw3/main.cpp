#include "TimeSumThread.h"

int main() {
    TimeSumThread timeSumThread;

    // Запускаем поток
    timeSumThread.start();

    // Добавляем данные в массив
    timeSumThread.add(10);
    timeSumThread.add(20);

    // Ждем 90 секунд, чтобы увидеть несколько выводов
    std::this_thread::sleep_for(std::chrono::seconds(90));

    // Удаляем данные из массива
    timeSumThread.remove(10);

    // Ждем еще 60 секунд
    std::this_thread::sleep_for(std::chrono::seconds(60));

    // Останавливаем поток
    timeSumThread.stop();

    return 0;
}
