import tkinter as tk
from tkinter import ttk
import subprocess
import sys
import re

def evaluate_expression(event=None):
    expression = entry_expr.get().strip()
    if not expression:
        return
    exe_path = "financial_calc.exe" if sys.platform == "win32" else "./financial_calc"
    
    try:
        process = subprocess.run(
            [exe_path] if sys.platform == "win32" else ["./financial_calc"],
            input=f"{expression}\nexit\n",
            capture_output=True,
            text=True,
            encoding='utf-8' 
        )
        
        output = process.stdout
        
        match = re.search(r'=> Result:\s*([0-9.-]+)', output)
        
        if match:
            lbl_result.config(text=match.group(1), foreground="#2E86C1") # 藍色顯示成功結果
        else:
            lbl_result.config(text="語法錯誤或無法解析", foreground="#E74C3C") # 紅色顯示錯誤
            print("C Engine Output:\n", output) # 在終端機印出除錯訊息
            
    except FileNotFoundError:
        lbl_result.config(text="找不到運算引擎！請先用 gcc/make 編譯 C 程式。", foreground="#E74C3C")

# --- UI 介面設計 ---
root = tk.Tk()
root.title("Financial & Calculus Engine UI")
root.geometry("450x250")
root.configure(padx=20, pady=20)
root.resizable(False, False)

lbl_title = ttk.Label(root, text="🧮 C-Powered Math Engine", font=("Segoe UI", 18, "bold"))
lbl_title.pack(pady=(0, 15))

frame_input = ttk.Frame(root)
frame_input.pack(fill="x", pady=5)

lbl_prompt = ttk.Label(frame_input, text="輸入算式: ", font=("Segoe UI", 12))
lbl_prompt.pack(side="left")

entry_expr = ttk.Entry(frame_input, font=("Consolas", 14), width=25)
entry_expr.pack(side="left", padx=5)
entry_expr.bind("<Return>", evaluate_expression)

btn_calc = ttk.Button(root, text="呼叫 C 引擎計算 (Calculate)", command=evaluate_expression)
btn_calc.pack(pady=15, fill="x", ipady=5)

frame_result = ttk.Frame(root)
frame_result.pack(fill="x", pady=5)

ttk.Label(frame_result, text="Result: ", font=("Segoe UI", 14, "bold")).pack(side="left")
lbl_result = ttk.Label(frame_result, text="---", font=("Consolas", 18, "bold"), foreground="#7F8C8D")
lbl_result.pack(side="left")

root.mainloop()