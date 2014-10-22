package com.mitusi020804.s02_08_handler04;

import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.ActionBarActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

/*
 * private static Message getPostMessage(Runnable r)该方法完成了两个操作
 * 1.生产了一个Message对象2.将r对象赋值给Runnable的callback属性
 * 第一个问题，如何把一个Runnable对象放入到消息队列中，
 * 实际上是生成了一个Message对象，然后将r对象赋值给Runnable的callback属性，然后在把Message对象放置在消息队列中
 * 第二个问题Looper取出了携带有r对象的Message对象之后干了些什么
 * 取出Message对象之后，调用了DispatchMessage方法，然后判断Message的callback属性是否为空，此时的callback属性有值
 * 所以执行了HandleCallback(Message msg)方法，在该方法当中执行了msg.callback.run()
 * */
public class MainActivity extends ActionBarActivity {

	private Button Btn;
	private Handler handler=new Handler();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        Btn=(Button)findViewById(R.id.button1);
        //匿名内部类
        Btn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				TestThread t=new TestThread();
				t.start();
			}
		});
    }
    
    class TestThread extends Thread
    {
    	@Override
    	public void run() {
    		// TODO Auto-generated method stub
    		super.run();
    		//匿名内部类
    		Runnable r=new Runnable() {
				
				@Override
				public void run() {
					// 这里可以写上更新UI的代码，相当于把这些更新代码放到主线程中运行
					String currentThreadName=Thread.currentThread().getName();
					System.out.println("当前线程的名称为："+currentThreadName);//结果输出为main
				}
				
			};
			//此方法将r对象放置在消息队列中。Looper对象（主线程）从消息队列中取出了r对象
			/*
			 * 我们的猜测：
			 * Thread t=new Thread(r)
			 * t.start();
			 * 但根据测试的结果证明猜测错误
			 * 所以Looper取出r之后干了什么，源代码Handler.java
			 * */
			handler.post(r);
    	}
    }


   
}
