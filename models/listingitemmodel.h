#ifndef LISTINGITEMMODEL_H
#define LISTINGITEMMODEL_H

#include <QList>
#include "disassemblermodel.h"
#include <core/disassembler/listing/listingdocument.h>

class ListingItemModel : public DisassemblerModel
{
    Q_OBJECT

    public:
        explicit ListingItemModel(size_t itemtype, QObject *parent = nullptr);
        void setDisassembler(const REDasm::DisassemblerPtr &disassembler) override;
        const REDasm::ListingItem* item(const QModelIndex& index) const;
        address_location address(const QModelIndex& index) const;

    public:
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        int rowCount(const QModelIndex& = QModelIndex()) const override;
        int columnCount(const QModelIndex& = QModelIndex()) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    protected:
        virtual bool isItemAllowed(const REDasm::ListingItem *item) const;

    private slots:
        void onListingChanged(const REDasm::ListingDocumentChanged *ldc);

    private:
        REDasm::sorted_container<address_t> m_items;
        size_t m_itemtype;

    friend class ListingFilterModel;
};

#endif // LISTINGITEMMODEL_H
