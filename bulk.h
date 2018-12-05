#pragma once

#include <list>
#include <string>
#include <ctime>

class ImpBulk
{
protected:
    std::list<std::string> _commands;
    time_t _beginTime;

public:
    virtual ~ImpBulk() {}

    virtual void appendCmd(std::string newCmd);
    virtual void clear(void);

    virtual void logCommands(void)   = 0;
    virtual void printCommands(void) = 0;

    virtual ImpBulk *clone(void)     = 0;
};

class Bulk : public ImpBulk
{
public:
    void logCommands(void) override;
    void printCommands(void) override;
    ImpBulk *clone(void) override;
};

class Bulker
{
    ImpBulk *_bulk;

public:
    Bulker(ImpBulk *bulk);
    void appendCmd(std::string &newCmd);
    void doWork(void);
};

class BulkController
{
    Bulker _bulker;
    size_t _commandsCount;
    size_t _currentNumber;
    std::string _signShiftUp;
    std::string _signShiftDown;
    size_t _stackSize;

public:
    BulkController(ImpBulk *bulk, int commandsCount);

    void getString(std::string &str);

    std::string signShiftUp() const;
    std::string signShiftDown() const;

    void setSignShiftUp(const std::string &signShiftUp);
    void setSignShiftDown(const std::string &signShiftDown);
};
