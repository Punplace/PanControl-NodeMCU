// 取得卡片類別資料，網頁端有用到
function getTypeData()
{
  return getOptionData("CardType");
}


// 取得進駐團隊資料，網頁端有用到
function getTeamData()
{
  return getOptionData("Team");
}


// 回傳 CardInfo 資料陣列
function ReturnCardInfoData(para)
{
  var cardNumber = para.CardNumber,
      owner = para.Owner,
      cardTypeID = para.CardTypeID,
      teamID = para.TeamID,
      createdTime = new Date().toLocaleString(); //取得現在時間
  
  return [cardNumber, owner, cardTypeID, teamID, createdTime];
}

