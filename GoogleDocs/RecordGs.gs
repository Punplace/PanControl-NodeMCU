// 取得卡片資料，網頁端有用到
function getCardData()
{
  return getOptionData("CardInfo");
}


// 取得機器資料，網頁端有用到
function getMachineData()
{
  return getOptionData("Machine");
}


// 回傳 Record 資料陣列
function ReturnRecordData(para)
{
  var cardID = para.CardID,
      machineID = para.MachineID,
      startTime = para.StartTime,
      endTime = para.EndTime; //取得現在時間
  
  return [cardID, machineID, startTime, endTime];
}

