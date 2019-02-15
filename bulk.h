#pragma once

#include <list>
#include <string>
#include <ctime>
#include <memory>


/*!
 * \brief ImpBulk интерфейс для бульков
 */
class ImpBulk
{
protected:
    std::list<std::string> _commands;   //!< Контейнер для хранения бульков
    time_t _beginTime;                  //!< Время записи первого элемента

public:
    virtual ~ImpBulk() {}

    /*!
     * \brief appendCmd Добаляет команду и сбрасывает таймер, если команда первая
     * \param newCmd Новая команда
     */
    virtual void appendCmd(const std::string &newCmd);

    /*!
     * \brief clear Очищает список команд
     */
    virtual void clear();

    /*!
     * \brief logCommands Записывает бульку в файл
     */
    virtual void logCommands() const = 0;

    /*!
     * \brief printCommands Выводит бульку на экран
     */
    virtual void printCommands() const = 0;

    /*!
     * \brief isEmpty Проверяет есть ли команды в бульке
     * \return
     */
    virtual bool isEmpty() const {return _commands.empty();}

};

/*!
 * \brief Bulk класс реализации бульки
 */
class Bulk : public ImpBulk
{
public:
    void logCommands() const override;
    void printCommands() const override;
};

/*!
 * \brief ImpWorker интерфейс для выполнения работы.
 */
struct ImpWorker
{
    virtual void operator ()(ImpBulk &bulk) = 0;
};

struct Worker : public ImpWorker
{
    void operator ()(ImpBulk &bulk) override;
};

/*!
 * \brief The BulkController
 * класс содержащий логику работы с бульками и логику заполнения булек
 */
class BulkController
{
    ImpBulk    &_bulk;
    ImpWorker  &_worker;
    size_t      _commandsCount;
    size_t      _currentNumber;
    size_t      _stackSize;
    std::string _signShiftUp;
    std::string _signShiftDown;

public:
    /*!
     * \brief BulkController конструктор
     * \param bulk указатель на бульку
     * \param commandsCount колличество команд в бульке
     */
    BulkController(int commandsCount, ImpBulk &bulk, ImpWorker &worker);

    /*!
     * \brief addString добавляет строку, если булька заполнена, выполняет соответствующие действия
     * \param str новая строка
     */
    void addString(const std::string &str);

    /*!
    * \brief flush выводит и очищает буффер
     * \param printInternalBlock если true будет напечатан незавершённый блок
     * не завершённые круппы команд вне блока выводятся всегда
     */
    void flush(bool printInternalBlock = false);

    std::string signShiftUp() const;
    std::string signShiftDown() const;

    void setSignShiftUp(const std::string &signShiftUp);
    void setSignShiftDown(const std::string &signShiftDown);
};
