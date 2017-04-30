# subsumtion

ardroneをルンバのように動かすための開発リポジトリ
![](image/gazebo.jpg)

ardroneのシミュレータ環境関係一式はここから
@[ardrone](https://github.com/lancer-evolution/ardrone)

## execution

ps3コントローラ及び、前方の回避行動
```bash
roslaunch subsumption ardrone_world.launch
rosrun joy joy_node
rosrun subsumtion psd
```

自動で動きまわる用
```bash
roslaunch subsumption ardrone_world.launch
rosrun subsumtion psd_auto
```

## detailes

* psd

* psd_auto
