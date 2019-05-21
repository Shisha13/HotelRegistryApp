#ifndef FILTERPROXYMODEL_H
#define FILTERPROXYMODEL_H
#include<QSortFilterProxyModel>

namespace logic
{

    enum class Filter
    {
        ALL_ROOMS,
        FREE_ROOMS,
        BOOKED_ROOMS
    };

    enum class SearchFilter
    {
        FREE_DATE,
        PERSON,
        CLASS,
        NONE
    };

    class FilterProxyModel : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        FilterProxyModel(QObject* parent = nullptr);
        ~FilterProxyModel() override {}
        bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
        void setSearchFilter(SearchFilter type, const QVariant& str);
        void setFilter(Filter type);
    protected:
        Filter _currentFilter = Filter::ALL_ROOMS;
        SearchFilter _currentSearch = SearchFilter::NONE;
        QVariant _searchData;
    };

}

#endif // FILTERPROXYMODEL_H§
