//Find in
bool CHARACTHER::DoRefine(LPITEM item, bool bMoneyOnly)
{
[...]
		DBManager::instance().SendMoneyLog(MONEY_LOG_REFINE, item->GetVnum(), -cost);
		NotifyRefineFail(this, item, IsRefineThroughGuild() ? "GUILD" : "POWER");
		item->AttrLog();
		ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE FAIL)");

		//PointChange(POINT_GOLD, -cost);
		PayRefineFee(cost);
	}
[...]
}

//Replace with
#ifdef ENABLE_HERRERO_BENDICION
		    DWORD result_fail_vnum = item->GetRefineFromVnum();
        // Fix perder items
        if (result_fail_vnum == 0)
        {
            return false;
        }
        //Final del fix
    		LPITEM pkNewItem = ITEM_MANAGER::instance().CreateItem(result_fail_vnum, 1, 0, true);
    		BYTE bCell = item->GetCell();
    		ITEM_MANAGER::CopyAllAttrTo(item, pkNewItem);
    		pkNewItem->AddToCharacter(this, TItemPos(INVENTORY, bCell)); 
  #else
    		DBManager::instance().SendMoneyLog(MONEY_LOG_REFINE, item->GetVnum(), -cost);
    		NotifyRefineFail(this, item, IsRefineThroughGuild() ? "GUILD" : "POWER");
    		item->AttrLog();
    		ITEM_MANAGER::instance().RemoveItem(item, "REMOVE (REFINE FAIL)");
  #endif

//Note
//PointChange(POINT_GOLD, -cost);    // if you want use money remove //
