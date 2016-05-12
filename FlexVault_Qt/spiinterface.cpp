#include "spiinterface.h"

SPIInterface::SPIInterface()
{

}

int SPIInterface::writeToFV(QString* sdb, unsigned int* cmd)
{
    unsigned int data = sdb->toInt();
    int fp, len, err;
    unsigned int value = 0;
    char txBuf[6];

    qDebug() << "writing...";

    fp = open("/dev/spidev0", O_RDWR);

    if(fp < 0)
    {
        qDebug() << "Open unsuccessful!";
        close(fp);
        return -1;
    }

    qDebug() << "data is:" << data;
    qDebug() << "cmd is:" << *cmd;

    value = *cmd + data;
    qDebug() << "value is:" << value;

    len = sprintf(txBuf, "%d", value);
    err = write(fp, txBuf, len);

    if (err <0)
    {
        qDebug() << "Write unsuccessful!";
        close(fp);
        return -1;
    }

    qDebug() << "value is now:" << value;
    close(fp);
    return 0;
}

int SPIInterface::readFromFV()
{
    int err, fp;
    char rxBuf[6];
    unsigned int value = 0;

    qDebug() << "reading...";

    fp = open("/dev/spidev0", O_RDWR);
    if (fp < 0)
    {
        qDebug() << "Open unsuccessful!";
        close(fp);
        return -1;
    }

    err = read(fp, &rxBuf, 6);

    if(err < 0)
    {
        qDebug() << "Read unsuccessful!";
        close(fp);
        return -1;
    }

    sscanf(rxBuf,"%i", &value);

    qDebug() << "value is:" << value;

    close(fp);

    return value;
}

