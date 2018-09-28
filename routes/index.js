var express = require('express');
var Code = require('../models/code');
var fs = require('fs');
var exec = require('child_process').exec;
var execFile = require('child_process').execFile;

var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {

  var data = fs.readFileSync('current.cpp','utf8');
  res.render('index', { title: 'Compiler' , code:data });

});

router.post('/',function(req,res,next){
  //console.log(req.body);
  

  var jug1 = req.body.jug1;
  var jug2 = req.body.jug2;
  var target = req.body.target;
  var input = jug1 + " " + jug2 + " " + target;
  console.log(target);
  fs.writeFileSync('input.txt',input);
  /*exec("g++ bfs.cpp -o r",function(err,std){
    if(err!== null)
    {
      console.log("output: ");
      //console.log(std);
      console.log(err);
      res.render('index',{title: 'compiler', out:err,result:false});
    }
    else {
      console.log("compiled");*/
      execFile('./r',function(error,stdout,stderr){

        console.log("output: ");
        console.log(stdout);
        res.render('index',{title: 'compiler', out:stdout,result:true});
      });

    /*}

  });*/

  

});


module.exports = router;
