import { lots } from "@/lib/mockData";
export default function Lots(){
  return (
    <div className="space-y-4">
      <div className="flex justify-between items-center">
        <h1 className="text-xl font-bold">Lot Creation & Quality Grading</h1>
        <button className="bg-krishi-600 text-white px-4 py-2 rounded text-sm">+ Create New Lot</button>
      </div>
      <div className="grid md:grid-cols-3 gap-4">
        {lots.map(l=>(
          <div key={l.id} className="bg-white p-4 rounded-xl border">
            <div className="flex justify-between"><span className="font-mono text-xs bg-gray-100 px-1 rounded">{l.id}</span><span className={`text-xs px-2 py-0.5 rounded ${l.status==="Listed"?"bg-blue-100 text-blue-700":l.status==="Graded"?"bg-green-100 text-green-700":"bg-orange-100 text-orange-700"}`}>{l.status}</span></div>
            <div className="mt-2 font-medium text-sm">{l.farmer}</div>
            <div className="text-sm">{l.commodity} • {l.qty} MT • Grade: {l.grade}</div>
            <div className="text-sm font-bold mt-1">Ask: ₹{l.priceAsk}/q</div>
            <div className="mt-3 flex gap-2">
              <button className="text-xs flex-1 bg-krishi-600 text-white py-1.5 rounded">List to Buyers</button>
              <button className="text-xs flex-1 border py-1.5 rounded">AI Grade (Photo)</button>
            </div>
            <div className="text-[11px] text-gray-500 mt-2">Digital contract • Escrow payment • Dispute support</div>
          </div>
        ))}
        <div className="border-2 border-dashed rounded-xl p-6 flex flex-col items-center justify-center text-sm text-gray-500">
          <div className="text-2xl">📸</div>
          <div className="font-medium">AI Quality Grading</div>
          <div className="text-xs text-center mt-1">Upload 3 photos (top, side, cut) → CNN grades size, color, defects per Agmark standards in 8s</div>
          <button className="mt-3 text-xs border px-3 py-1 rounded">Try Demo</button>
        </div>
      </div>
      <div className="bg-white p-4 rounded-xl border">
        <h3 className="font-semibold text-sm">FPO Aggregation</h3>
        <p className="text-xs text-gray-600 mt-1">Pool lots from 5-50 smallholders into 20-100 MT truck-loads. Enables bulk negotiation (+₹80-150/q), shared logistics, and single payment split via UPI. Current: Solapur Tur Dal cluster (40 MT, 23 farmers) matched to Mid-Day Meal Authority at ₹10,200/q.</p>
      </div>
    </div>
  );
}
