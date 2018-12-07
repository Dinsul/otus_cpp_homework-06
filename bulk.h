#pragma once

#include <list>
#include <string>
#include <ctime>


/*!
 * \brief The ImpBulk class
 * Интерфейс для бульков
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
    virtual void appendCmd(std::string newCmd);

    /*!
     * \brief clear Очищает список команд
     */
    virtual void clear(void);

    /*!
     * \brief logCommands Записывает бульку в файл
     */
    virtual void logCommands(void)   = 0;

    /*!
     * \brief printCommands Выводит бульку на экран
     */
    virtual void printCommands(void) = 0;

    /*!
     * \brief clone Создаёт новый класс потомка
     * \return  указатель на новый экземпляр
     */
    virtual ImpBulk *clone(void)     = 0;
};

/*!
 * \brief The Bulk class
 * Реализация бульки
 */
class Bulk : public ImpBulk
{
public:
    void logCommands(void) override;
    void printCommands(void) override;
    ImpBulk *clone(void) override;
};

/*!
 * \brief The Bulker
 * класс для работы с бульками
 */
class Bulker
{
    ImpBulk *_bulk;

public:
    Bulker(ImpBulk *bulk);
    void appendCmd(std::string &newCmd);
    void doWork(void);
};

/*!
 * \brief The BulkController
 * класс содержащий логику работы с бульками и логику заполнения булек
 */
class BulkController
{
    Bulker _bulker;
    size_t _commandsCount;
    size_t _currentNumber;
    std::string _signShiftUp;
    std::string _signShiftDown;
    size_t _stackSize;

public:
    /*!
     * \brief BulkController конструктор
     * \param bulk указатель на бульку
     * \param commandsCount колличество команд в бульке
     */
    BulkController(ImpBulk *bulk, int commandsCount);

    /*!
     * \brief addString добавляет строку, если булька заполнена, выполняет соответствующие действия
     * \param str новая строка
     */
    void addString(std::string &str);

    std::string signShiftUp() const;
    std::string signShiftDown() const;

    void setSignShiftUp(const std::string &signShiftUp);
    void setSignShiftDown(const std::string &signShiftDown);
};
