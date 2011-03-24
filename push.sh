#!/bin/bash
set -u
set -e

OUTPUT="" 

ssh -i ~/ec2/Neba-Laptop.pem ubuntu@ec2-46-51-161-60.eu-west-1.compute.amazonaws.com "rm -rf ~/development/elog/*" 2>&1 $OUTPUT
echo $OUTPUT

scp -r -p -i /Users/barryodriscoll/ec2/Neba-Laptop.pem /Users/barryodriscoll/Documents/crc_workspace/elog/* ubuntu@ec2-46-51-161-60.eu-west-1.compute.amazonaws.com:/home/ubuntu/development/elog 2>&1 $OUTPUT
echo $OUTPUT

ssh -i ~/ec2/Neba-Laptop.pem ubuntu@ec2-46-51-161-60.eu-west-1.compute.amazonaws.com "source /home/ubuntu/.profile; cd /home/ubuntu/development/elog; pwd; bjam --clean release toolset=gcc; bjam release toolset=gcc; ./bin/gcc/release/elog > email.txt" 2>&1 $OUTPUT
echo $OUTPUT