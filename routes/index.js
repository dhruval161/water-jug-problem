var express = require('express');
var Code = require('../models/code');
var fs = require('fs');
var exec = require('child_process').exec;
var execFile = require('child_process').execFile;

var router = express.Router();

/* GET home page. */

router.get('/jugs3', function(req, res, next) {

  var data = fs.readFileSync('current.cpp','utf8');
  res.render('jugs3', { title: 'Compiler' , code:data });

});

router.get('/', function(req, res, next) {

  var data = fs.readFileSync('current.cpp','utf8');
  res.render('index', { title: 'Compiler' , code:data });

});

router.post('/jugs3',function(req,res,next){
  console.log(req.body);
  console.log('submitted');

  var jug1 = req.body.jug1;
  var jug2 = req.body.jug2;
  var jug3 = req.body.jug3;
  var jug1r = req.body.jug1r;
  var jug2r = req.body.jug2r;
  var jug3r = req.body.jug3r;

  var input = "3 ";
  

  input += jug1 +' '+ jug2+' '+ jug3+' ';

  input += jug1r + ' '+ jug2r +' '+ jug3r ;

  console.log(input);

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
        res.render('jugs3',{title: 'compiler', out:stdout,result:true});
      });

    /*}

  });*/

  

});

router.post('/',function(req,res,next){
  console.log(req.body);
  

  var jug1 = req.body.jug1;
  var jug2 = req.body.jug2;
  var jug1r = req.body.jug1r;
  var jug2r = req.body.jug2r;
  var total = req.body.total;

  var input = "2 ";
  if(req.body.restrict)
  {
    input += '1 ';
  }
  else{
    input += '0 ';
  }

  input += jug1 +' '+ jug2+' ';
  if(req.body.restrict){
    input+= total +' ';
  }

  input += jug1r + ' '+ jug2r ;

  console.log(input);

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
