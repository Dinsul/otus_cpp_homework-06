#include "bulk.h"

#include <iostream>
#include <fstream>

#include <stdexcept>

void Bulk::logCommands()
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

void Bulk::printCommands()
{
    std::cout << "bulk: ";

    for (auto cmd : _commands)
    {
        std::cout << cmd << " ";
    }

    std::cout << std::endl;
}

ImpBulk *Bulk::clone()
{
    return new Bulk();
}

void ImpBulk::appendCmd(std::string newCmd)
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

BulkController::BulkController(ImpBulk *bulk, int commandsCount)
    : _bulker(bulk), _commandsCount(commandsCount), _currentNumber(0),
      _signShiftUp("{"), _signShiftDown("}")
{}

void BulkController::addString(std::string &str)
{
    if (str == _signShiftUp)
    {
        if (_stackSize == 0)
        {
            _bulker.doWork();
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
            _bulker.doWork();
            _currentNumber = 0;
        }
    }
    else
    {
        _bulker.appendCmd(str);

        ++_currentNumber;

        if (_stackSize == 0 && _currentNumber == _commandsCount)
        {
            _currentNumber = 0;
            _bulker.doWork();
        }
    }
}

Bulker::Bulker(ImpBulk *bulk) : _bulk(bulk)
{
}

void Bulker::appendCmd(std::string &newCmd)
{
    _bulk->appendCmd(newCmd);
}

void Bulker::doWork()
{
    if (!_bulk->isEmpty())
    {
        _bulk->printCommands();
        _bulk->logCommands();
        _bulk->clear();
    }
}
