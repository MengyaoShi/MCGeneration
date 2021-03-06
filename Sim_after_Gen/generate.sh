#!/bin/bash
#parse arguments
if [ $# -ne 5 ]
    then
    echo "Usage: ./generate.sh cfg_name script_name dir_name queue number_of_files"
    exit 0
fi

cfg_name=$1
script_name=$2
dir_name=$3
queue=$4
number_of_files=$5

mkdir -p BSUB/$dir_name
cd BSUB/$dir_name

#make directory on EOS
EOS_dir_query=`cmsLs /store/user/mshi/${dir_name}`
EOS_dir_query=`echo $EOS_dir_query | grep "No such file or directory"`
if [ "EOS_dir_query" != "" ]
    then
    cmsMkdir /store/user/mshi/${dir_name}
fi

#PUT FOR LOOP HERE REPLACING NUM WITH OTHER NUMBER
COUNT=0
while [ $COUNT -lt $number_of_files ]; do
  let COUNT=COUNT+1
  sed -e "s%DIRNAME%${dir_name}%g" -e "s%NUM%${COUNT}%g" ../../${cfg_name}.py >  ${cfg_name}_${dir_name}_${COUNT}.py
  sed -e "s%GENERATOR%${cfg_name}_${dir_name}_${COUNT}%g" -e "s%NUM%${COUNT}%g" -e "s%DIRNAME%${dir_name}%g" ../../${script_name}.sh > ${script_name}_${dir_name}_${COUNT}.sh
  echo "Count= $COUNT"
  chmod u+x ${script_name}_${dir_name}_${COUNT}.sh
  bsub -q $queue -J ${cfg_name}_${dir_name}_${COUNT} < ${script_name}_${dir_name}_${COUNT}.sh
done

cd ../../
