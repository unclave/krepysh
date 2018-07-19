#include <QCoreApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{

    QSharedMemory mem;
    mem.setKey("MyKey");
    if (!mem.attach()) // подключаемся к уже созданной памяти
    {
    //.... // если не удалось
    }
    char *data = (char*)mem.data(); // указатель на общую память
    if (mem.lock())
    {
      QByteArray ar;
      for (int i=0;data[i];i++)
        ar.append(data[i]);
      mem.unlock();
      // теперь массив ar содержит строку "Hello", которую передало другое приложение
    }
    QCoreApplication a(argc, argv);
    return a.exec();
}
