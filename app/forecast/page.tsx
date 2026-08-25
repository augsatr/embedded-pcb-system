import PriceChart from "@/components/PriceChart";
import { saleWindowAdvice } from "@/lib/mockData";
export default function Forecast(){
  return (
    <div className="space-y-6">
      <h1 className="text-xl font-bold">Sale-Window Recommendation Engine (AI)</h1>
      <PriceChart />
      <div className="grid md:grid-cols-3 gap-4">
        <div className="md:col-span-2 bg-white p-5 rounded-xl border">
          <h3 className="font-semibold">Why HOLD?</h3>
          <ul className="text-sm list-disc ml-5 mt-2 space-y-1 text-gray-700">
            <li>Arrival volumes fell 18% WoW at Lasalgaon/Pune - supply tightness.</li>
            <li>Retail demand +12% (Ganesh Chaturthi stocking).</li>
            <li>Weather model: no heavy rain next 10 days in Nashik belt - no dump risk.</li>
            <li>Storage viability: NAFED Junnar warehouse 2km - ₹45/q/week, covers 14 days hold vs +₹240/q gain.</li>
          </ul>
          <div className="mt-4 grid grid-cols-3 gap-2 text-xs">
            <div className="p-2 bg-green-50 rounded text-center"><div className="font-bold text-green-700">₹3,120/q</div><div>Predicted peak (31 Aug)</div></div>
            <div className="p-2 bg-orange-50 rounded text-center"><div className="font-bold text-orange-700">₹45/q/week</div><div>Storage cost</div></div>
            <div className="p-2 bg-blue-50 rounded text-center"><div className="font-bold text-blue-700">Net +8.4%</div><div>Gain after costs</div></div>
          </div>
          <div className="mt-4 text-xs text-gray-500">Model: LSTM + XGBoost on 3 years Agmarknet daily prices, arrivals, IMD rainfall, and buyer bid volumes. Accuracy MAPE 8.3%. Updates daily 6 AM.</div>
        </div>
        <div className="bg-white p-5 rounded-xl border">
          <h3 className="font-semibold">Action</h3>
          <button className="w-full mt-3 bg-krishi-600 text-white py-2 rounded text-sm">Create Lot & Schedule for 31 Aug</button>
          <button className="w-full mt-2 border py-2 rounded text-sm">Set Price Alert at ₹3,000</button>
          <div className="mt-4 p-3 bg-gray-50 rounded text-xs">
            <div className="font-medium">Risk Controls</div>
            <div className="mt-1">• Auto-notify if forecast drops &gt;5%</div>
            <div>• One-click logistics booking</div>
            <div>• FPO aggregation option: pool with 23 farmers for bulk buyer</div>
          </div>
        </div>
      </div>
    </div>
  );
}
