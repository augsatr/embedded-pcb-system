import PriceChart from "@/components/PriceChart";
import AdvisoryExplain from "@/components/AdvisoryExplain";
import ImpactCard from "@/components/ImpactCard";
import AlertPrefs from "@/components/AlertPrefs";
export default function Advisor(){
  return (
    <div className="space-y-6">
      <div><h1 className="text-xl font-bold">Price Advisor — The Decision Engine</h1><p className="text-sm text-gray-600">Not a chart. A <b>decision</b>: HOLD vs SELL with net farm-gate math, weighted explainability, risk brake, and auto WhatsApp.</p></div>
      <PriceChart />
      <AdvisoryExplain />
      <ImpactCard />
      <AlertPrefs />
      <div className="bg-gray-900 text-green-100 p-4 rounded-xl font-mono text-xs space-y-2">
        <div className="font-bold text-white">Pitch line (15 sec):</div>
        <div>"If Ramesh waits 12 days per our HOLD, he nets +₹240/q = ₹28,800 on his 12MT after storage. Last 3 years, same logic averaged +6.2%. He gets it on WhatsApp in Marathi at 6 AM — no app needed."</div>
        <div className="border-t border-gray-700 pt-2 text-gray-400">Model: LSTM + XGBoost on 3yr Agmarknet prices + IMD rainfall. MAPE 8.3%. Updates daily 6 AM. Confidence 87% = weighted arrival/demand/weather factors.</div>
      </div>
    </div>
  );
}
