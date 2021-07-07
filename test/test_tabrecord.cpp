#include <gtest.h>

#include "tabrecord.h"

TEST(TTabRecord, CanCreate) {
    EXPECT_NO_THROW(TTabRecord tr("", nullptr));
}

TEST(TTabRecord, CanGetCopy) {
    TTabRecord tr("", nullptr);

    PTTabRecord ptr = (PTTabRecord)tr.GetCopy();

    EXPECT_EQ(tr, *ptr);
}
