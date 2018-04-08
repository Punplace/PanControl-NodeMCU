var _db = SpreadsheetApp.getActiveSpreadsheet(); //取得資料庫(對應的 GoogleSheet)


// 初始化，網址後面得加上 ?PageName=頁名 ，即可回傳對應的值或 html 頁面
// Ex: https://script.google.com/macros/s/key/exec?PageName=CardInfo
function doGet(e)
{
  // Logger.log( Utilities.jsonStringify(e) );
  
  var pageName = e.parameter.PageName;
  var htmlTemplate;
  
  if (pageName == null) {
    return ContentService.createTextOutput("No PageName");
    //return ContentService.createTextOutput("請在網址後傳送 PageName ");
  }
  else if(pageName == "Arduino"){
    var result = "Hello Arduino!";
    return ContentService.createTextOutput(result);
  }
  else{
    htmlTemplate = HtmlService.createTemplateFromFile(pageName);
  }
  
  // 還可以直接塞給這頁變數，神奇的寫法..
  // <form>的action，有點像是要送出的位址，這邊放"最新的程式碼測試 網路應用程式網址"
  htmlTemplate.actionUrl = "https://script.google.com/macros/s/AKfycbz46PadqPv4C4F91evN9LaR8evKg-iOgn5VzoNHdFM/dev";
  
  // htmlTemplate.actionUrl = "https://script.google.com/macros/s/AKfycbyu5QsO0fHaBZQ84m4u_zCBnZqMRa9UxOv0KsQyScwQ8gT7Y2Y/exec";
  // OS:網址後面的/dev與/exec 可以想成兩個 Web App
  // 開發執行最新程式碼是dev那個，隨時更新隨時變動
  // exec那個只有 **發佈+新增版本** 才會變動
  // 結論！用dev那串比較省事...，然後 GoogleSite 連結要用exec
  
  return htmlTemplate.evaluate();
}


// 按下送出，會執行這裡
function doPost(e)
{
  // e.parameter 裡存放所有傳送的參數
  var result = AddData(e.parameter);
  
  return ContentService.createTextOutput(result);
}


// 新增資料
function AddData(para)
{
  // 前面要有個隱藏欄位(hidden)傳 TableName
  var tableName = para.TableName;
  if(tableName == null){
    return "沒有 TableName！";
  }
  
  // 各頁所傳的資料陣列，用 switch 去對應方法撈出來
  var dataArray;
  
  switch(tableName)
  {
    case "CardInfo":
      dataArray = ReturnCardInfoData(para);
      break;
    case "CardType":
      dataArray = ReturnCardTypeData(para);
      break;
    case "Team":
      dataArray = ReturnTeamData(para);
      break;
    case "Machine":
      dataArray = ReturnMachineData(para);
      break;
    case "Record":
      dataArray = ReturnRecordData(para);
      break;
    default:
      return "沒有這個表，檢查一下你的 TableName 吧";
  }
  
  var table = _db.getSheetByName(tableName);
  
  // 用總列數去生id
  var id = table.getLastRow() - table.getFrozenRows() + 1;
  
  // 把 id 加到陣列第一個
  dataArray.unshift(id);
  
  // 插入一列新的資料 
  table.appendRow(dataArray);
  
  return "已成功新增~~~";
}


// 嵌入頁面，重複程式碼可用，但有gs的不行，因為是 HtmlOutput 而不是 Template
// 官方範例是用於把 css 和 javaScript 抽出去
function Include(filename) {
  return HtmlService.createHtmlOutputFromFile(filename)
      .getContent();
  // 使用：<?!= Include('Stylesheet'); ?>
}


// 下拉選單取資料副程式
// <sheetName> 表的名稱
function getOptionData(tableName)
{
  var table = _db.getSheetByName(tableName);
  
  var startRow = 3, //開始列
      startColumn = 1, //開始欄
      columnLength = 2, //取2欄就好，[key, value]
      rowLength = table.getLastRow() - table.getFrozenRows(); //總列數

  var data = table.getRange(startRow, startColumn, rowLength, columnLength).getValues();
  
  return data;
}

