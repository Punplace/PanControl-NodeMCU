// 回傳 CardType 資料陣列
function ReturnCardTypeData(para)
{
  var name = para.Name;
  
  return [name];
}


// 回傳 Team 資料陣列
function ReturnTeamData(para)
{
  var name = para.Name;
  Logger.log(para.IsActive);
  var isActive = (para.IsActive == 'on')? 'True' : 'False';
  
  return [name, isActive];
}


// 回傳 Machine 資料陣列
function ReturnMachineData(para)
{
  var name = para.Name;
  var charge = para.Charge;
  
  return [name, charge];
}

