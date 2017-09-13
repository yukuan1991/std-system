#include "DetailedInfoTable.h"
#include <QHeaderView>

#include <QDebug>

DetailedInfoTable::DetailedInfoTable(QWidget *parent)
    : QTableWidget(parent)
{

}

void DetailedInfoTable::load(const QString &method, const QVariant &data)
{
    if(method.isEmpty())
    {
        return;
    }

    if(data.isNull())
    {
        return;
    }

    if(method == "视频分析法")
    {
        loadVaf(data);
    }
    else if(method == "预定工时法")
    {
        loadPts(data);
    }
    else if(method == "标准资料法")
    {
        loadStd(data);
    }
    else
    {
        return;
    }

}

void DetailedInfoTable::loadVaf(const QVariant &data)
{
    const auto formData = data.toMap()["form"];
    const auto jobContent = formData.toMap()["作业内容"].toList();
    const auto rows = jobContent.size();
    if(rows <= 0)
    {
        return;
    }

    setRowCount(rows);
    QStringList headerList;
    headerList << "编号" << "作业内容";

    for(int i = 0; i < 20; i++)
    {
        auto observationHeader = std::to_string(i / 2 + 1);
        if(i % 2 == 0)
        {
            headerList << (observationHeader + "T").data();
        }
        else
        {
            headerList << (observationHeader + "R").data();
        }
    }
    headerList << "平均时间" << "评比系数" << "基本时间" << "宽放率" << "标准时间" << "增值/非增值" << "操作分类";
    const auto cols = headerList.size();
    setColumnCount(cols);
    setHorizontalHeaderLabels(headerList);
    verticalHeader()->hide();

    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            setItem(row, col, new QTableWidgetItem);
            item(row, col)->setTextAlignment(Qt::AlignCenter);
            setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    }

    const auto numPosition = std::find(headerList.begin(), headerList.end(), "编号");
    const auto numCol = numPosition - headerList.begin();
    const auto jobContentPosition = std::find(headerList.begin(), headerList.end(), "作业内容");
    const auto jobContentCol = jobContentPosition - headerList.begin();
    const auto averageTimePosition = std::find(headerList.begin(), headerList.end(), "平均时间");
    const auto averageTimeCol = averageTimePosition - headerList.begin();
    const auto comparisonPosition = std::find(headerList.begin(), headerList.end(), "评比系数");
    const auto comparisonCol = comparisonPosition - headerList.begin();
    const auto basicPosition = std::find(headerList.begin(), headerList.end(), "基本时间");
    const auto basicCol = basicPosition - headerList.begin();
    const auto ratePosition = std::find(headerList.begin(), headerList.end(), "宽放率");
    const auto rateCol = ratePosition - headerList.begin();
    const auto stdTimePosition = std::find(headerList.begin(), headerList.end(), "标准时间");
    const auto stdTimeCol = stdTimePosition - headerList.begin();
    const auto valueAddedPosition = std::find(headerList.begin(), headerList.end(), "增值/非增值");
    const auto valueAddedCol = valueAddedPosition - headerList.begin();
    const auto typePosition = std::find(headerList.begin(), headerList.end(), "操作分类");
    const auto typeCol = typePosition - headerList.begin();


    const auto resultData = formData.toMap()["结果"].toList();
    for(int row = 0; row < rows; row++)
    {
        item(row, numCol)->setData(Qt::DisplayRole, row + 1);
        item(row, jobContentCol)->setData(Qt::DisplayRole, jobContent.at(row));
        item(row, averageTimeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["平均时间"]);
        item(row, comparisonCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["评比系数"]);
        item(row, basicCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["基本时间"]);
        item(row, rateCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["宽放率"]);
        item(row, stdTimeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["标准时间"]);
        item(row, valueAddedCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["增值/非增值"]);
        item(row, typeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["操作分类"]);
    }


    const auto observationData = formData.toMap()["观测时间"].toList();

    if(observationData.size() == 0)
    {
        return;
    }

    const auto positionT = std::find(headerList.begin(), headerList.end(), "1T");
    const auto startColT = positionT - headerList.begin();
    const auto positionR = std::find(headerList.begin(), headerList.end(), "1R");
    const auto startColR = positionR - headerList.begin();

    for(int i = 0; i < observationData.size(); i++)
    {
        const auto groupList = observationData.at(i).toList();

        for(int j = 0; j < groupList.size(); j++)
        {
            const auto dataT = groupList.at(j).toMap()["T"];

            const auto dataR = groupList.at(j).toMap()["R"];

            if(dataT > 0)
            {
                item(j, startColT + 2 * i)->setData(Qt::DisplayRole, dataT);
            }
            else
            {
                item(j, startColT + 2 * i)->setData(Qt::DisplayRole, QVariant{});
            }

            if(dataR > 0)
            {
                item(j, startColR + 2 * i)->setData(Qt::DisplayRole, dataR);
            }
            else
            {
                item(j, startColR + 2 * i)->setData(Qt::DisplayRole, QVariant{});
            }
        }
    }
}

void DetailedInfoTable::loadPts(const QVariant &data)
{
    const auto formData = data.toMap()["form"];
    const auto totalCountData = formData.toMap()["总计"].toList();
    const auto rows = totalCountData.size();
    if(rows <= 0)
    {
        return;
    }

    setRowCount(rows);
    QStringList headerList;
    headerList << "作业内容" << "代码" << "数量*频次" << "MOD/TMU" << "评比系数" << "基本时间" << "宽放率" << "标准时间"
               << "增值/非增值" << "操作分类";

    const auto cols = headerList.size();
    setColumnCount(cols);
    setHorizontalHeaderLabels(headerList);

    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            setItem(row, col, new QTableWidgetItem);
            item(row, col)->setTextAlignment(Qt::AlignCenter);
            setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    }

    int jobContentCol = -1;
    int codeCol = -1;
    int numCol = -1;
    int modTmuCol = -1;
    int comparisonCol = -1;
    int basicTimeCol = -1;
    int rateCol = -1;
    int stdTimeCol = -1;
    int valueAddedCol = -1;
    int typeCol = -1;

    const auto jobContentFound = std::find(headerList.begin(), headerList.end(), "作业内容");
    if(jobContentFound != headerList.end())
    {
        jobContentCol = jobContentFound - headerList.begin();
    }
    const auto codeFound = std::find(headerList.begin(), headerList.end(), "代码");
    if(codeFound != headerList.end())
    {
        codeCol = codeFound - headerList.begin();
    }
    const auto numFound = std::find(headerList.begin(), headerList.end(), "数量*频次");
    if(numFound != headerList.end())
    {
        numCol = numFound - headerList.begin();
    }
    auto modTmuFound = std::find(headerList.begin(), headerList.end(), "MOD/TMU");
    if(modTmuFound != headerList.end())
    {
        modTmuCol = modTmuFound - headerList.begin();
    }
    const auto comparisonFound = std::find(headerList.begin(), headerList.end(), "评比系数");
    if(comparisonFound != headerList.end())
    {
        comparisonCol = comparisonFound - headerList.begin();
    }
    const auto basicTimeFound = std::find(headerList.begin(), headerList.end(), "基本时间");
    if(basicTimeFound != headerList.end())
    {
        basicTimeCol = basicTimeFound - headerList.begin();
    }
    const auto rateFound = std::find(headerList.begin(), headerList.end(), "宽放率");
    if(rateFound != headerList.end())
    {
        rateCol = rateFound - headerList.begin();
    }
    const auto stdTimeFound = std::find(headerList.begin(), headerList.end(), "标准时间");
    if(stdTimeFound != headerList.end())
    {
        stdTimeCol = stdTimeFound - headerList.begin();
    }
    const auto valueAddedFound = std::find(headerList.begin(), headerList.end(), "增值/非增值");
    if(valueAddedFound != headerList.end())
    {
        valueAddedCol = valueAddedFound - headerList.begin();
    }
    const auto typeFound = std::find(headerList.begin(), headerList.end(), "操作分类");
    if(typeFound != headerList.end())
    {
        typeCol = typeFound - headerList.begin();
    }

    for(int row = 0; row < rows; row++)
    {
        const auto tableMap = totalCountData.at(row).toMap();
        if(!tableMap["作业内容"].isNull() and jobContentCol != -1)
        {
            item(row, jobContentCol)->setData(Qt::DisplayRole, tableMap["作业内容"]);
        }
        if(!tableMap["代码"].isNull() and codeCol != -1)
        {
            const auto codeList = tableMap["代码"].toList();
            QString code;
            int i = 0;
            for(auto & it : codeList)
            {
                const auto list = it.toString().split("_");
                if(list.size() == 2)
                {
                    code += list.at(1);
                }
                if(i < codeList.size() - 1)
                {
                    code += ".";
                }
                i++;
            }
            item(row, codeCol)->setData(Qt::DisplayRole, code);
        }
        if(!tableMap["数量*频次"].isNull() and numCol != -1)
        {
            item(row, numCol)->setData(Qt::DisplayRole, tableMap["数量*频次"]);
        }
        if(!tableMap["MOD"].isNull() and modTmuCol != -1)
        {
            item(row, modTmuCol)->setData(Qt::DisplayRole, tableMap["MOD"]);
        }
        else if(!tableMap["TMU"].isNull() and modTmuCol != -1)
        {
            item(row, modTmuCol)->setData(Qt::DisplayRole, tableMap["TMU"]);
        }
        if(!tableMap["评比系数"].isNull() and comparisonCol != -1)
        {
            item(row, comparisonCol)->setData(Qt::DisplayRole, comparisonCol);
        }
        if(!tableMap["基本时间"].isNull() and basicTimeCol != -1)
        {
            item(row, basicTimeCol)->setData(Qt::DisplayRole, tableMap["基本时间"]);
        }
        if(!tableMap["宽放率"].isNull() and rateCol != -1)
        {
            item(row, rateCol)->setData(Qt::DisplayRole, tableMap["宽放率"]);
        }
        if(!tableMap["标准时间"].isNull() and stdTimeCol != -1)
        {
            item(row, stdTimeCol)->setData(Qt::DisplayRole, tableMap["标准时间"]);
        }
        if(!tableMap["增值/非增值"].isNull() and valueAddedCol != -1)
        {
            item(row, valueAddedCol)->setData(Qt::DisplayRole, tableMap["增值/非增值"]);
        }
        if(!tableMap["操作分类"].isNull() and typeCol != -1)
        {
            item(row, typeCol)->setData(Qt::DisplayRole, tableMap["操作分类"]);
        }
    }

}

void DetailedInfoTable::loadStd(const QVariant &data)
{
    const auto formData = data.toMap()["form"];
    const auto jobContent = formData.toMap()["作业内容"].toList();
    const auto rows = jobContent.size();
    if(rows <= 0)
    {
        return;
    }

    setRowCount(rows);
    QStringList headerList;
    headerList << "作业内容" << "公司内部代码" << "标准操作单元作业内容" << "历史来源" << "预定工时法总代码" << "标准操作单元基本时间"
               << "数量*频次" << "基本时间" << "宽放率" << "标准时间" << "增值/非增值" << "操作分类";

    const auto cols = headerList.size();
    setColumnCount(cols);
    setHorizontalHeaderLabels(headerList);

    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            setItem(row, col, new QTableWidgetItem);
            item(row, col)->setTextAlignment(Qt::AlignCenter);
            setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    }


    int jobContentCol = -1;
    int companyCodeCol = -1;
    int stdOperationUnitCol = -1;
    int historyCol = -1;
    int totalCodeCol = -1;
    int stdUnitTimeCol = -1;
    int numCol = -1;
    int basicTimeCol = -1;
    int rateCol = -1;
    int stdTimeCol = -1;
    int valueAddedCol = -1;
    int typeCol = -1;

    const auto jobContentFound = std::find(headerList.begin(), headerList.end(), "作业内容");
    if(jobContentFound != headerList.end())
    {
        jobContentCol = jobContentFound - headerList.begin();
    }
    const auto companyCodeFound = std::find(headerList.begin(), headerList.end(), "公司内部代码");
    if(companyCodeFound != headerList.end())
    {
        companyCodeCol = companyCodeFound - headerList.begin();
    }
    const auto stdOperationUnitFound = std::find(headerList.begin(), headerList.end(), "标准操作单元作业内容");
    if(stdOperationUnitFound != headerList.end())
    {
        stdOperationUnitCol = stdOperationUnitFound - headerList.begin();
    }
    const auto historyFound = std::find(headerList.begin(), headerList.end(), "历史来源");
    if(historyFound != headerList.end())
    {
        historyCol = historyFound - headerList.begin();
    }
    const auto totalCodeFound = std::find(headerList.begin(), headerList.end(), "预定工时法总代码");
    if(totalCodeFound != headerList.end())
    {
        totalCodeCol = totalCodeFound - headerList.begin();
    }
    const auto stdUnitTimeFound = std::find(headerList.begin(), headerList.end(), "标准操作单元基本时间");
    if(stdUnitTimeFound != headerList.end())
    {
        stdUnitTimeCol = stdUnitTimeFound - headerList.begin();
    }
    const auto numFound = std::find(headerList.begin(), headerList.end(), "数量*频次");
    if(numFound != headerList.end())
    {
        numCol = numFound - headerList.begin();
    }
    const auto basicTimeFound = std::find(headerList.begin(), headerList.end(), "基本时间");
    if(basicTimeFound != headerList.end())
    {
        basicTimeCol = basicTimeFound - headerList.begin();
    }
    const auto rateFound = std::find(headerList.begin(), headerList.end(), "宽放率");
    if(rateFound != headerList.end())
    {
        rateCol = rateFound - headerList.begin();
    }
    const auto stdTimeFound = std::find(headerList.begin(), headerList.end(), "标准时间");
    if(stdTimeFound != headerList.end())
    {
        stdTimeCol = stdTimeFound - headerList.begin();
    }
    const auto valueAddedFound = std::find(headerList.begin(), headerList.end(), "增值/非增值");
    if(valueAddedFound != headerList.end())
    {
        valueAddedCol = valueAddedFound - headerList.begin();
    }
    const auto typeFound = std::find(headerList.begin(), headerList.end(), "操作分类");
    if(typeFound != headerList.end())
    {
        typeCol = typeFound - headerList.begin();
    }



    const auto resultData = formData.toMap()["结果"].toList();
    for(int row = 0; row < rows; row++)
    {
        if(!jobContent.at(row).isNull() and jobContentCol != -1)
        {
            item(row, jobContentCol)->setData(Qt::DisplayRole, jobContent.at(row));
        }
        if(!resultData.at(row).toMap()["公司内部代码"].isNull() and companyCodeCol != -1)
        {
            item(row, companyCodeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["公司内部代码"]);
        }
        if(!resultData.at(row).toMap()["标准操作单元作业内容"].isNull() and stdOperationUnitCol != -1)
        {
            item(row, stdOperationUnitCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["标准操作单元作业内容"]);
        }
        if(!resultData.at(row).toMap()["历史来源"].isNull() and historyCol != -1)
        {
            item(row, historyCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["历史来源"]);
        }
        if(!resultData.at(row).toMap()["预定工时法总代码"].isNull() and totalCodeCol != -1)
        {
            item(row, totalCodeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["预定工时法总代码"]);
        }
        if(!resultData.at(row).toMap()["标准操作单元基本时间"].isNull() and stdUnitTimeCol != -1)
        {
            item(row, stdUnitTimeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["标准操作单元基本时间"]);
        }
        if(!resultData.at(row).toMap()["数量*频次"].isNull() and numCol != -1)
        {
            item(row, numCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["数量*频次"]);
        }
        if(!resultData.at(row).toMap()["基本时间"].isNull() and basicTimeCol != -1)
        {
            item(row, basicTimeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["基本时间"]);
        }
        if(!resultData.at(row).toMap()["宽放率"].isNull() and rateCol != -1)
        {
            item(row, rateCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["宽放率"]);
        }
        if(!resultData.at(row).toMap()["标准时间"].isNull() and stdTimeCol != -1)
        {
            item(row, stdTimeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["标准时间"]);
        }
        if(!resultData.at(row).toMap()["增值/非增值"].isNull() and valueAddedCol != -1)
        {
            item(row, valueAddedCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["增值/非增值"]);
        }
        if(!resultData.at(row).toMap()["操作分类"].isNull() and typeCol != -1)
        {
            item(row, typeCol)->setData(Qt::DisplayRole, resultData.at(row).toMap()["操作分类"]);
        }
    }
}
