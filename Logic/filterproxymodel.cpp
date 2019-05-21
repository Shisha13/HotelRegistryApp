#include "filterproxymodel.h"
#include "room.h"

using namespace logic;

FilterProxyModel::FilterProxyModel(QObject* parent)
    :QSortFilterProxyModel (parent)
{

}

bool FilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    bool allRoomsSearch = Filter::ALL_ROOMS == _currentFilter;
    if(allRoomsSearch && SearchFilter::NONE == _currentSearch)
    {
        return true;
    }
    const COLUMNS column = SearchFilter::CLASS == _currentSearch ? COLUMNS::CLASS : COLUMNS::ORDERS;
    auto index = sourceModel()->index(sourceRow, static_cast<int>(column), QModelIndex());

    switch (_currentSearch)
    {
    case SearchFilter::FREE_DATE:
    {
        const auto& orders = index.data().value<OrdersList>().orders;
        const QDate& searchDate = _searchData.toDate();
        const auto it = std::find_if(orders.cbegin(), orders.cend(),[searchDate](const Order& order)
        {
            return searchDate >= order.dateIn  && searchDate <= order.dateOut;
        });
        if(it != orders.cend())
        {
            return false;
        }
        return true;
    }
    case SearchFilter::PERSON:
    {
        const auto& orders = index.data().value<OrdersList>().orders;
        const QString& name = _searchData.toString().toLower();
        const auto it = std::find_if(orders.cbegin(), orders.cend(),[name](const Order& order)
        {
            for(const auto& person : order.persons)
            {
                if(person.name.toLower().contains(name))
                {
                    return true;
                }
            }
            return false;
        });
        if(it != orders.cend())
        {
            return false;
        }
        return true;
    }
    case SearchFilter::CLASS:
    {
        const QString& searchClass = _searchData.toString();
        return index.data().toString().contains(searchClass);
    }
    }
    return false;
}

void FilterProxyModel::setSearchFilter(SearchFilter type, const QVariant& data)
{
    _searchData = data;
    _currentSearch = type;
    invalidateFilter();
}

void FilterProxyModel::setFilter(Filter type)
{
    _currentFilter = type;
    invalidateFilter();
}
