#include "bulk.h"

#include <iostream>
#include <fstream>

#include <stdexcept>

void Bulk::logCommands() const
{
    auto fileName = std::string("bulk") + std::to_string(_beginTime) + ".log";

    std::ofstream logFile;

    logFile.open(fileName, std::ios_base::app);

    logFile << "bulk: ";

    for (auto cmd : _commands)
        logFile << cmd << " ";

    logFile << std::endl;

    logFile.close();
}

void Bulk::printCommands() const
{
    std::cout << "bulk: ";

    for (auto cmd : _commands)
    {
        std::cout << cmd << " ";
    }

    std::cout << std::endl;
}

void ImpBulk::appendCmd(const std::string &newCmd)
{
    if (isEmpty())
    {
        _beginTime = time(NULL);
    }

    _commands.push_back(newCmd);
}

void ImpBulk::clear()
{
    _commands.clear();
}

std::string BulkController::signShiftDown() const
{
    return _signShiftDown;
}

void BulkController::setSignShiftDown(const std::string &signShiftDown)
{
    _signShiftDown = signShiftDown;
}

std::string BulkController::signShiftUp() const
{
    return _signShiftUp;
}

void BulkController::setSignShiftUp(const std::string &signShiftUp)
{
    _signShiftUp = signShiftUp;
}

BulkController::BulkController(int commandsCount, ImpBulk &bulk, ImpWorker &worker)
    : _bulk(bulk), _worker(worker),
      _commandsCount(commandsCount), _currentNumber(0),
      _stackSize(0), _signShiftUp("{"), _signShiftDown("}")
{}

void BulkController::addString(const std::string &str)
{
    if (str == _signShiftUp)
    {
        if (_stackSize == 0)
        {
            _worker(_bulk);
        }

        ++_stackSize;
    }
    else if (str == _signShiftDown)
    {
        if (_stackSize == 0)
        {
            throw std::out_of_range("stack breakdown below");
        }

        --_stackSize;

        if (_stackSize == 0)
        {
            _worker(_bulk);
            _currentNumber = 0;
        }
    }
    else
    {
        _bulk.appendCmd(str);

        ++_currentNumber;

        if (_stackSize == 0 && _currentNumber == _commandsCount)
        {
            _currentNumber = 0;
            _worker(_bulk);
        }
    }
}

void BulkController::flush(bool printInternalBlock)
{
    if (!printInternalBlock && _stackSize > 0)
    {
        return;
    }

    _worker(_bulk);
}


void Worker::operator ()(ImpBulk &bulk)
{
    bulk.printCommands();
    bulk.logCommands();
    bulk.clear();
}
