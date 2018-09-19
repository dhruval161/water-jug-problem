var Code = require('../models/code');
var mongoose = require('mongoose');

mongoose.connect('mongodb://localhost:27017/mydb');

var hello = new Code({
  name : 'Hello world',
  lang: 'cpp',
  src: '#include<iostream>' + '\n'+
  'using namespace std;' +'\n' +
  'int main()'+ '\n' +
  '{'+ '\n' +
  '  cout<<"Hello World"<<endl;'+ '\n' +
  '  return 0;'+ '\n' +
  '}' + '\n'
});

hello.save(function(err,result){
  exit();
});

function exit()
{
  mongoose.disconnect();
}
